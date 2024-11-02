#include "AtomMatrix.hh"
#include <cassert>
#include <iostream>
#include <random>
#include <tbb/tbb.h>
#include <thread>
#include <vector>
constexpr auto block_width = AtomMatrix<double>::size();
template <size_t bs>
constexpr auto blocked_index(size_t i, size_t j)
{
    auto ib = i / bs;
    i = i % bs;
    auto jb = j / bs;
    j = j % bs;
    return std::make_tuple(ib, jb, i, j);
}
inline auto morton(unsigned r, unsigned c) -> unsigned
{
    constexpr unsigned mask[] { 0xaaaaaaaa, 0x55555555 };
    auto rr = _pdep_u32(r, mask[0]);
    auto cc = _pdep_u32(c, mask[1]);
    return rr | cc;
}
auto ran01() -> double
{
    static thread_local std::minstd_rand engine { std::hash<std::thread::id> {}(std::this_thread::get_id()) };
    static thread_local std::uniform_real_distribution<> dist;
    return dist(engine);
}
struct BlockMatrix {
    static constexpr auto nblk = 8UL;
    using value_type = double;
    std::array<AtomMatrix<double>, nblk * nblk> blks;
    auto block(size_t i, size_t j) -> AtomMatrix<double>&
    {
        return blks[nblk * i + j];
    }
    auto block(size_t i, size_t j) const -> const AtomMatrix<double>&
    {
        return blks[nblk * i + j];
    }
    auto operator()(size_t i, size_t j) const -> const value_type&
    {
        auto [ib, jb, ii, jj] = blocked_index<block_width>(i, j);
        return blks[nblk * ib + jb](ii, jj);
    }
    auto operator()(size_t i, size_t j) -> value_type&
    {
        auto [ib, jb, ii, jj] = blocked_index<block_width>(i, j);
        return blks[nblk * ib + jb](ii, jj);
    }

    constexpr auto n_blocks() const noexcept { return nblk; }
    static constexpr auto size() noexcept { return nblk * block_width; }
    template <class G>
    void fill(G& gen)
    {
        for (auto& b : blks)
            b.fill(gen);
    }
    void operator=(double x)
    {
        for (auto& b : blks)
            b = x;
    }
    struct BMProd {
        const BlockMatrix& lhs;
        const BlockMatrix& rhs;
    };
    void operator+=(BMProd prod);
};
auto operator*(const BlockMatrix& L, const BlockMatrix& R) -> BlockMatrix::BMProd
{
    return { L, R };
}
void BlockMatrix::operator+=(BlockMatrix::BMProd prod)
{
    for (size_t i = 0UL; i < n_blocks(); ++i) {
        for (size_t j = 0UL; j < n_blocks(); ++j) {
            auto tmp = block(i, j).to_row_blocks();
            for (size_t k = 0UL; k < prod.lhs.n_blocks(); ++k)
                mul(tmp, prod.lhs.block(i, k), prod.rhs.block(k, j));
            block(i, j).from_row_blocks(tmp);
        }
    }
}

template <class BlockType>
struct matrix_view {
    BlockType* org = nullptr;
    static constexpr auto incore_thresh = 64UL;
    size_t nel = 0;
    struct BlockProd {
        const matrix_view lhs;
        const matrix_view rhs;
    };
    void operator+=(typename matrix_view<const BlockType>::BlockProd prod)
    {
        assert(nel == prod.lhs.nel && nel == prod.rhs.nel);
        if (nel == 1) {
            org[0] += (prod.lhs.org[0] * prod.rhs.org[0]);
        } else {
            auto sz = nel / 4;
            auto Lrg = prod.lhs.org;
            auto Rrg = prod.rhs.org;
            matrix_view tl { org, sz }, tr { org + sz, sz }, bl { org + 2 * sz, sz }, br { org + 3 * sz, sz };
            matrix_view<const BlockType> Ltl { Lrg, sz }, Ltr { Lrg + sz, sz }, Lbl { Lrg + 2 * sz, sz }, Lbr { Lrg + 3 * sz, sz };
            matrix_view<const BlockType> Rtl { Rrg, sz }, Rtr { Rrg + sz, sz }, Rbl { Rrg + 2 * sz, sz }, Rbr { Rrg + 3 * sz, sz };
            if (nel > incore_thresh) {
                tbb::parallel_invoke(
                    [&] {
                        tl += (Ltl * Rtl);
                        tl += (Ltr * Rbl);
                    },
                    [&] {
                        tr += (Ltl * Rtr);
                        tr += (Ltr * Rbr);
                    },
                    [&] {
                        bl += (Lbl * Rtl);
                        bl += (Lbr * Rbl);
                    },
                    [&] {
                        br += (Lbl * Rtr);
                        br += (Lbr * Rbr);
                    });
            } else {
                tl += (Ltl * Rtl);
                tl += (Ltr * Rbl);
                tr += (Ltl * Rtr);
                tr += (Ltr * Rbr);
                bl += (Lbl * Rtl);
                bl += (Lbr * Rbl);
                br += (Lbl * Rtr);
                br += (Lbr * Rbr);
            }
        }
    }
};

template <class B>
auto operator*(const matrix_view<B>& l, const matrix_view<B>& r) -> typename matrix_view<B>::BlockProd
{
    return { l, r };
}

class matrix {
public:
    using value_type = double;
    using BlockType = BlockMatrix;
    static constexpr size_t block_grain_size = BlockType::size();
    auto nrows() const -> size_t { return nr; }
    auto ncols() const -> size_t { return nc; }
    static_assert(block_grain_size != 0UL && ((block_grain_size & (block_grain_size - 1)) == 0),
        "Block matrix must have 2^N x 2^N shape");
    struct matprod {
        const matrix& lhs;
        const matrix& rhs;
    };
    matrix(size_t i, size_t j)
        : nr { i }
        , nc { j }
    {
        auto nerr = 0;
        if ((i & (i - 1)) != 0) {
            std::cerr << "Recursive block matrix only works with powers of 2 dimensions. N_rows given as " << i << "\n";
            ++nerr;
        }
        if ((j & (j - 1)) != 0) {
            std::cerr << "Recursive block matrix only works with powers of 2 dimensions. N_cols given as " << j << "\n";
            ++nerr;
        }
        if (nerr != 0)
            exit(1);
        dat.resize((nr / block_grain_size) * (nc / block_grain_size));
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
        tbb::parallel_for(0UL, dat.size(), [&](auto i) {
            dat[i].fill(ran01);
        });
    }
    auto operator*(const matrix& m) const -> matprod
    {
        assert(nc == m.nr);
        return { *this, m };
    }
    auto operator=(const matprod& p) -> matrix&
    {
        operator=(0.);
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
        matrix_view<BlockType> C { dat.data(), dat.size() };
        matrix_view<const BlockType> A { p.lhs.dat.data(), p.lhs.dat.size() };
        matrix_view<const BlockType> B { p.rhs.dat.data(), p.rhs.dat.size() };
        C += (A * B);
        return *this;
    }
    auto operator()(size_t i, size_t j) const -> const value_type&
    {
        constexpr auto bs = block_grain_size;
        auto blkloc = morton(i / bs, j / bs);
        std::cerr << "Mapping index " << i << ", " << j << " to (" << i % bs << ", " << j % bs
                  << ") on Morton ordered block " << blkloc << "\n";
        return dat[blkloc](i % bs, j % bs);
    }
    auto operator()(size_t i, size_t j) -> value_type&
    {
        constexpr auto bs = block_grain_size;
        auto blkloc = morton(i / bs, j / bs);
        return dat[blkloc](i % bs, j % bs);
    }

private:
    std::vector<BlockType, tbb::cache_aligned_allocator<BlockType>> dat;
    size_t nr { 1 }, nc { 1 };
};
