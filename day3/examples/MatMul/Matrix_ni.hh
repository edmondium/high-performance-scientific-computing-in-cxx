#include "AtomMatrix.hh"
#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <random>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
#include <tbb/cache_aligned_allocator.h>
#include <thread>
#include <vector>

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

constexpr auto block_width = AtomMatrix<double>::size();

struct alignas(CACHELINE_SIZE) BlockMatrix {
    static constexpr auto nblk = 64UL;
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
    auto operator()(size_t i, size_t j) const -> value_type
    {
        auto[ib, jb, ii, jj] = blocked_index<block_width>(i, j);
        return blks[nblk * ib + jb](ii, jj);
    }
    auto operator()(size_t i, size_t j) -> value_type&
    {
        auto[ib, jb, ii, jj] = blocked_index<block_width>(i, j);
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
};

void mul(BlockMatrix& C, const BlockMatrix& A, const BlockMatrix& B)
{
    for (size_t i = 0UL; i < C.n_blocks(); ++i) {
        for (size_t j = 0UL; j < C.n_blocks(); ++j) {
            auto tmp = C.block(i, j).to_row_blocks();
            for (size_t k = 0UL; k < A.n_blocks(); ++k)
                mul(tmp, A.block(i, k), B.block(k, j));
            C.block(i, j).from_row_blocks(tmp);
        }
    }
}

class matrix {
public:
    using value_type = double;
    auto nrows() const -> size_t { return nr; }
    auto ncols() const -> size_t { return nc; }
    static constexpr auto block_grain_size() -> size_t { return BlockMatrix::size(); }
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
        add_blockwise_product(p);
        return *this;
    }
    auto operator()(size_t i, size_t j) const -> value_type
    {
        constexpr auto bs = block_grain_size();
        auto nblk = nr / bs;
        auto[ib, jb, ii, jj] = blocked_index<bs>(i, j);
        return dat[nblk * ib + jb](ii, jj);
    }
    auto operator()(size_t i, size_t j) -> value_type&
    {
        constexpr auto bs = block_grain_size();
        auto nblk = nr / bs;
        auto[ib, jb, ii, jj] = blocked_index<bs>(i, j);
        return dat[nblk * ib + jb](ii, jj);
    }

private:
    void add_blockwise_product(const matprod& p)
    {
        const auto nblk = nr / block_grain_size();
        tbb::blocked_range<size_t> R(0UL, nblk);
        tbb::parallel_for(R, [&](tbb::blocked_range<size_t> r) {
            for (size_t ib = r.begin(); ib < r.end(); ++ib) {
                for (size_t kb = 0; kb < nblk; ++kb) {
                    const auto& Aik = p.lhs.dat[ib * nblk + kb];
                    for (size_t jb = 0; jb < nblk; ++jb) {
                        if (kb == 0)
                            dat[ib * nblk + jb] = 0.;
                        mul(dat[ib * nblk + jb], Aik, p.rhs.dat[kb * nblk + jb]);
                    }
                }
            }
        });
    }
    using BlockType = BlockMatrix;
    std::vector<BlockType, tbb::cache_aligned_allocator<BlockType>> dat;
    size_t nr{ 1 }, nc{ 1 };
};
