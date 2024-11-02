#include <cassert>
#include <vector>
#include <tbb/tbb.h>

#ifndef CACHELINE_SIZE
#define CACHELINE_SIZE 32
#endif

template <typename D>
struct CacheLine {
    static constexpr size_t nvars = CACHELINE_SIZE / sizeof(D);
};
constexpr auto block_width = 4 * CacheLine<double>::nvars;

template <class MatrixType>
class MatrixView {
public:
    using value_type = double;
    auto ncols() const { return static_cast<const MatrixType*>(this)->ncols(); }
    auto nrows() const { return static_cast<const MatrixType*>(this)->nrows(); }
    auto data() -> value_type* { return static_cast<MatrixType*>(this)->data(); }
    auto data() const -> const value_type* { return static_cast<const MatrixType*>(this)->data(); }
    auto operator()(size_t i, size_t j) const -> value_type { return data()[i * ncols() + j]; }
    auto operator()(size_t i, size_t j) -> value_type& { return data()[i * ncols() + j]; }
    auto row(size_t i) const -> const value_type* { return data() + i * ncols(); }
    auto row(size_t i) -> value_type* { return data() + i * ncols(); }
    auto operator=(value_type v) -> MatrixView&
    {
        for (size_t i = 0; i < nrows() * ncols(); ++i)
            data()[i] = v;
        return *this;
    }
};
namespace details {
template <class T>
void simple_ikj_mult(MatrixView<T>& C, const MatrixView<T>& A, const MatrixView<T>& B)
{
    // Note: We do not zero out matrix C here. It is assumed that matrix C is
    // already zero initialised elsewhere. We only add contributions to C.
    assert(A.ncols() == B.nrows());
    assert(C.nrows() == A.nrows());
    assert(C.ncols() == B.ncols());
    for (auto i = 0ul; i < C.nrows(); ++i) {
        for (auto k = 0ul; k < A.ncols(); ++k) {
            auto aik = A(i,k);
//            auto * crowi = C.row(i);
//            auto * browk = B.row(k);
            // Using the __restrict__ keyword on the pointers crowi and browk
            // seems to benefit performance with GCC by about 10%, while it has
            // no effect in clang. __restrict__ is a language extension in C++,
            // and not a standard feature. It is implemented by many compilers
            // to do what the C99 keyword "restrict" does. It may be called
            // _restrict, __restrict, _restrict_ by different compilers.
            auto * __restrict__ crowi = C.row(i);
            auto * __restrict__ browk = B.row(k);
            for (auto j = 0ul; j < C.ncols(); ++j) {
                crowi[j] += aik * browk[j];
            }
        }
    }
}
}
template <class VT, size_t N>
class alignas(CACHELINE_SIZE) FixedSizeMatrix : public MatrixView<FixedSizeMatrix<VT, N>> {
    VT d[N * N];

public:
    using value_type = VT;
    auto nrows() const -> size_t { return N; }
    auto ncols() const -> size_t { return N; }
    auto data() -> value_type* { return d; }
    auto data() const -> const value_type* { return d; }
    using MatrixView<FixedSizeMatrix<VT, N>>::operator=;
};

class matrix {
public:
    using value_type = double;
    auto nrows() const -> size_t { return nr; }
    auto ncols() const -> size_t { return nc; }
    struct matprod {
        const matrix& lhs;
        const matrix& rhs;
    };
    matrix(size_t i, size_t j)
        : nr{ i }
        , nc{ j }
    {
        dat.resize((nr / block_width) * (nc / block_width));
    }
    void resize(size_t i, size_t j)
    {
        nr = i;
        nc = j;
        dat.resize((nr / block_width) * (nc / block_width));
    }
    matrix() = default;
    matrix(const matrix&) = delete;
    matrix(matrix&&) = default;
    auto operator=(matrix m) -> matrix&
    {
        swap(m);
        return *this;
    }
    void swap(matrix& m)
    {
        std::swap(nr, m.nr);
        std::swap(nc, m.nc);
        dat.swap(m.dat);
    }
    template <class G>
    void fill(G& gen)
    {
        for (size_t i = 0; i < dat.size(); ++i) {
            for (size_t j = 0; j < dat[i].nrows(); ++j) {
                for (size_t k = 0; k < dat[i].ncols(); ++k) {
                    dat[i](j, k) = gen();
                }
            }
        }
    }
    auto operator*(const matrix& m) const -> matprod
    {
        assert(nc == m.nr);
        return { *this, m };
    }
    auto operator=(const matprod& p) -> matrix&;
    auto operator=(double x) -> matrix&
    {
        for (auto i = 0ul; i < dat.size(); ++i)
            dat[i] = x;
        return *this;
    }
    auto operator+=(const matprod& p) -> matrix&
    {
        add_blockwise_product(p);
        return *this;
    }

private:
    void add_blockwise_product(const matprod & p) {
        const auto nblk = nr / block_width;
        tbb::blocked_range<size_t> R(0ul, nblk);
        tbb::parallel_for(R, [&](tbb::blocked_range<size_t> r) {
            for (size_t ib = r.begin(); ib < r.end(); ++ib) {
                for (size_t jb = 0; jb < nblk; ++jb) {
                    for (size_t kb = 0; kb < nblk; ++kb) {
                        details::simple_ikj_mult(dat[ib * nblk + jb],
                            p.lhs.dat[ib * nblk + kb],
                            p.rhs.dat[kb * nblk + jb]);
                    }
                }
            }
        });
    }
    std::vector<FixedSizeMatrix<double, block_width>> dat;
    size_t nr{ 1 }, nc{ 1 };
};

auto matrix::operator=(const matrix::matprod& p) -> matrix&
{
    const auto nblk = nr / block_width;
    for (size_t ib = 0; ib < nblk; ++ib) {
        for (size_t jb = 0; jb < nblk; ++jb) {
            dat[ib * nblk + jb] = 0.;
        }
    }
    return operator+=(p);
}
