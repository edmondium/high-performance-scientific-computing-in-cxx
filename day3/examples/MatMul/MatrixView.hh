#pragma once
#include <cassert>
#include <cstddef>
#include <execution>
#include <span>
// #define MANUAL_VECTORIZATION 1
#ifdef MANUAL_VECTORIZATION
#include <xsimd/xsimd.hpp>
#endif

template <class MatrixType, class VT>
class MatrixView {
public:
    using value_type = VT;
    auto impl() const -> const MatrixType& { return *static_cast<const MatrixType*>(this); }
    auto impl() -> MatrixType& { return *static_cast<MatrixType*>(this); }
    auto ncols() const { return impl().ncols_(); }
    auto nrows() const { return impl().nrows_(); }
    auto row(size_t i) const -> const value_type* { return impl().row_(i); }
    auto row(size_t i) -> value_type* { return impl().row_(i); }
    auto operator()(size_t i, size_t j) const -> const value_type& { return row(i)[j]; }
    auto operator()(size_t i, size_t j) -> value_type& { return row(i)[j]; }

    auto operator=(value_type v) -> MatrixView&
    {
        for (size_t i = 0; i < nrows(); ++i)
            for (size_t j = 0; j < ncols(); ++j)
                row(i)[j] = v;
        return *this;
    }
};
namespace details {
#ifndef MANUAL_VECTORIZATION
template <class T>
void row_scale(std::span<T> out, std::span<const T> inp, T scl)
{
    std::transform(
        // std::execution::unseq,
        inp.begin(), inp.end(), out.begin(),
        out.begin(),
        [scl](auto&& x, auto&& y) { return scl * x + y; });
}
#else
struct row_scaler_t {
    template <class T, class Arch>
    void operator()(Arch, std::span<T> out, std::span<const T> inp, T scl) const
    {
        using b_type = xsimd::batch<T, Arch>;
        constexpr auto bsize = b_type::size;
        auto blkaik = b_type::broadcast(scl);
        auto vsize = out.size() - out.size() % bsize;
        for (auto j = 0UL; j < vsize; j += bsize) {
            auto blkc = b_type::load_aligned(&out[j]);
            auto blkb = b_type::load_aligned(&inp[j]);
            blkc = xsimd::fma(blkaik, blkb, blkc);
            blkc.store_aligned(&out[j]);
        }
        for (auto j = vsize; j < out.size(); ++j) {
            out[j] += scl * inp[j];
        }
    }
};
inline auto row_scale = xsimd::dispatch(row_scaler_t {});
#endif

template <class T, class VT>
void simple_ikj_mult(MatrixView<T, VT>& C, const MatrixView<T, VT>& A,
    const MatrixView<T, VT>& B)
{
    // Note: We do not zero out matrix C here. It is assumed that matrix C is
    // already zero initialised elsewhere. We only add contributions to C.
    assert(A.ncols() == B.nrows());
    assert(C.nrows() == A.nrows());
    assert(C.ncols() == B.ncols());
    for (auto i = 0UL; i < C.nrows(); ++i) {
        for (auto k = 0UL; k < A.ncols(); ++k) {
            auto aik = A(i, k);
            auto* crowi = C.row(i);
            auto* browk = B.row(k);
            row_scale(std::span(crowi, C.ncols()), std::span(browk, C.ncols()), aik);
            //            for (auto j = 0ul; j < C.ncols(); ++j) {
            //                crowi[j] += aik * browk[j];
            //            }
        }
    }
}

}
