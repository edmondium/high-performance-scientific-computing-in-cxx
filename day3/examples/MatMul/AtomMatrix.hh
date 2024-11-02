#pragma once

#include <xsimd/xsimd.hpp>
#include "cache_props.hh"

using Arch = xsimd_Arch;
template <class T>
using simdType = xsimd::batch<T, Arch>;

#include <array>
#include <iostream>
template <size_t imin, size_t imax>
struct uloop {
    template <class F>
    [[gnu::always_inline]] auto operator()(F&& f) const
    {
        if constexpr (imin < imax) {
            f(imin);
            uloop<imin + 1, imax> {}(std::forward<F>(f));
        }
    }
};

template <class T>
class alignas(CACHELINE_SIZE) AtomMatrix {
public:
    using row_block_type = simdType<T>;
    static constexpr auto size() { return row_block_type::size; }

    using row_blocks = std::array<row_block_type, size()>;

    auto operator()(size_t i, size_t j) const noexcept -> const T& { return m[i * size() + j]; }
    auto operator()(size_t i, size_t j) noexcept -> T& { return m[i * size() + j]; }

    auto to_row_blocks() const -> row_blocks
    {
        std::array<row_block_type, size()> rows;
        uloop<0UL, size()> {}([&](size_t i) {
            rows[i] = row_block_type::load_aligned(&m[i * size()]);
        });
        return rows;
    }
    static auto clean_new_row_blocks() -> row_blocks
    {
        row_blocks ans;
        for (auto& rw : ans)
            rw = row_block_type::broadcast(T {});
        return ans;
    }
    void from_row_blocks(const row_blocks& rows)
    {
        uloop<0ul, size()> {}([&](size_t i) {
            rows[i].store_aligned(&m[i * size()]);
        });
    }
    void operator=(const T& t)
    {
        std::fill(m.begin(), m.end(), t);
    }

    void operator=(const row_blocks& rows)
    {
        from_row_blocks(rows);
    }
    template <class G>
    void fill(G& gen)
    {
        std::generate_n(m.begin(), size() * size(), gen);
    }

private:
    std::array<T, size() * size()> m;
};

template <class T>
void mul(typename AtomMatrix<T>::row_blocks& crows,
    const AtomMatrix<T>& A, const AtomMatrix<T>& B)
{
    constexpr auto size = AtomMatrix<T>::size();
    using row_type = typename AtomMatrix<T>::row_block_type;
    auto brows = B.to_row_blocks();
    uloop<0ul, size> {}([&](size_t k) { // k-i-j loop order!
        uloop<0ul, size> {}([&](size_t i) {
            crows[i] = xsimd::fma<T, Arch>(row_type::broadcast(A(i, k)), brows[k], crows[i]);
        });
    });
}

template <class T>
void mul(AtomMatrix<T>& C, const AtomMatrix<T>& A, const AtomMatrix<T>& B)
{
    auto crows = AtomMatrix<T>::clean_new_row_blocks();
    mul_aa(crows, A, B);
    C.from_row_blocks(crows);
}

// int main()
//{
//     AtomMatrix<double> a, b, c;
//     a = 0.; b= 0.; c=0.;
//     a(1,2) = a(2,1) = -1.;
//     b(1,2) = b(2,1) = 1.;
//     b(0,1) = b(0,2) = -1.0; b(0,0) = b(0,3) = 2.0;
//     a(0,1) = a(0,2) = 1.0; a(0,0) = a(0,3) = 3.0;
//     a(3,1) = a(3,2) = 1.0; a(3,0) = a(3,3) = 3.0;
//     mul(c, a, b);
//     for (int i = 0; i<4; ++i) {
//         for (int j = 0; j<4; ++j) {
//             std::cout << c(i,j) << " ";
//         }
//         std::cout << "\t";
//         for (int j = 0; j<4; ++j) {
//             std::cout << a(i,j) << " ";
//         }
//         std::cout << "\t";
//         for (int j = 0; j<4; ++j) {
//             std::cout << b(i,j) << " ";
//         }
//         std::cout << "\n";
//     }
// }
