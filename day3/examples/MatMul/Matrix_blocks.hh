#include "MatrixView.hh"
#include "CountingIterator.hh"
#include "cache_props.hh"
#include <tuple>
#include <vector>
#include <random>
#include <thread>
#include <algorithm>
#include <execution>

constexpr auto block_width = 256UL;
template <size_t bs>
auto blocked_index(size_t i, size_t j)
{
    auto ib = i / bs;
    i = i % bs;
    auto jb = j / bs;
    j = j % bs;
    return std::make_tuple(ib, jb, i, j);
}
auto ran01() -> double
{
    static thread_local std::minstd_rand engine{ std::hash<std::thread::id>{}(std::this_thread::get_id()) };
    static thread_local std::uniform_real_distribution<> dist;
    return dist(engine);
}

template <class VT, size_t N>
class alignas(CACHELINE_SIZE) FixedSizeMatrix : public MatrixView<FixedSizeMatrix<VT, N>, VT> {
    VT d[N * N];

public:
    using value_type = VT;
    constexpr auto nrows_() const noexcept -> size_t { return N; }
    constexpr auto ncols_() const noexcept -> size_t { return N; }
    constexpr auto row_(size_t i) -> value_type* { return &d[i * N]; }
    constexpr auto row_(size_t i) const -> const value_type* { return &d[i * N]; }
    auto operator()(size_t i, size_t j) const -> const value_type& { return row_(i)[j]; }
    auto operator()(size_t i, size_t j) -> value_type& { return row_(i)[j]; }
    using MatrixView<FixedSizeMatrix<VT, N>, VT>::operator=;
};

class matrix {
public:
    using value_type = double;
    static constexpr auto block_grain_size() -> size_t { return block_width; }
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
        dat.resize((nr / block_grain_size()) * (nc / block_grain_size()));
    }
    void resize(size_t i, size_t j)
    {
        nr = i;
        nc = j;
        dat.resize((nr / block_grain_size()) * (nc / block_grain_size()));
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
    void random_fill()
    {
        std::for_each(std::execution::par,
	              algo_counter(0UL), algo_counter(dat.size()),
		      [&](auto i) {
            for (size_t j = 0; j < dat[i].nrows(); ++j) {
                for (size_t k = 0; k < dat[i].ncols(); ++k) {
                    dat[i](j, k) = ran01();
                }
            }
        });
    }
    auto operator*(const matrix& m) const -> matprod
    {
        assert(nc == m.nr);
        return { *this, m };
    }
    auto operator=(const matprod& p) -> matrix&
    {
        const auto nblk = nr / block_grain_size();
        for (size_t ib = 0; ib < nblk; ++ib) {
            for (size_t jb = 0; jb < nblk; ++jb) {
                dat[ib * nblk + jb] = 0.;
            }
        }
        return operator+=(p);
    }
    auto operator=(double x) -> matrix&
    {
        for (auto i = 0UL; i < dat.size(); ++i)
            dat[i] = x;
        return *this;
    }
    auto operator+=(const matprod& p) -> matrix&
    {
        add_blockwise_product(p);
        return *this;
    }
    auto operator()(size_t i, size_t j) const -> value_type
    {
        auto[ib, jb, ii, jj] = blocked_index<block_grain_size()>(i, j);
        const auto nblk = nr / block_grain_size();
        return dat[nblk * ib + jb](ii, jj);
    }
    auto operator()(size_t i, size_t j) -> value_type&
    {
        auto[ib, jb, ii, jj] = blocked_index<block_grain_size()>(i, j);
        const auto nblk = nr / block_grain_size();
        return dat[nblk * ib + jb](ii, jj);
    }

private:
    void add_blockwise_product(const matprod& p);
    std::vector<FixedSizeMatrix<double, block_width>> dat;
    size_t nr{ 1 }, nc{ 1 };
};

void matrix::add_blockwise_product(const matprod& p)
{
    const auto nblk = nr / block_width;
    std::for_each(std::execution::par, algo_counter(0UL),
        algo_counter(nblk * nblk),
        [&](auto ijb) {
            auto [ib, jb] = std::ldiv(ijb, nblk);
                for (size_t kb = 0; kb < nblk; ++kb) {
                    details::simple_ikj_mult(dat[ib * nblk + jb],
                        p.lhs.dat[ib * nblk + kb],
                        p.rhs.dat[kb * nblk + jb]);
                }
        });
}

