#ifndef MATRIXVIEW_HH
#define MATRIXVIEW_HH
#include <cstddef>
#include <cassert>
template <class MatrixType>
class MatrixView {
public:
    using value_type = double;
    auto impl() const -> const MatrixType& { return *static_cast<const MatrixType*>(this); }
    auto impl() -> MatrixType& { return *static_cast<MatrixType*>(this); }
    auto ncols() const { return impl().ncols_(); }
    auto nrows() const { return impl().nrows_(); }
    auto row(size_t i) const -> const value_type* { return impl().row_(i); }
    auto row(size_t i) -> value_type* { return impl().row_(i); }
    auto operator()(size_t i, size_t j) const -> value_type { return row(i)[j]; }
    auto operator()(size_t i, size_t j) -> value_type& { return row(i)[j]; }

    auto operator=(value_type v) -> MatrixView&
    {
        for (size_t i = 0; i < nrows(); ++i)
            for (size_t j = 0; j < ncols(); ++j)
                row(i)[j] = v;
        return *this;
    }
};
#include "simd_wrapper.hh"
namespace details {
template <class T>
void simple_ikj_mult(MatrixView<T>& C, const MatrixView<T>& A, const MatrixView<T>& B)
{
    // Note: We do not zero out matrix C here. It is assumed that matrix C is
    // already zero initialised elsewhere. We only add contributions to C.
    assert(A.ncols() == B.nrows());
    assert(C.nrows() == A.nrows());
    assert(C.ncols() == B.ncols());
    using VT = typename MatrixView<T>::value_type;
    for (auto i = 0ul; i < C.nrows(); ++i) {
        for (auto k = 0ul; k < A.ncols(); ++k) {
            auto aik = A(i,k);
            auto * crowi = C.row(i);
            auto * browk = B.row(k);
// #define MANUAL_VECTORIZATION
#ifndef MANUAL_VECTORIZATION
            for (auto j = 0ul; j < C.ncols(); ++j) {
                crowi[j] += aik * browk[j];
            }
#else
            auto blkaik = simdlib::set_simd(aik);
            for (auto j = 0ul; j < C.ncols(); j += simdlib::simd_type<VT>::size) {
                auto blkc = simdlib::load_aligned(crowi + j);
                auto blkb = simdlib::load_aligned(browk + j);
                blkc = simdlib::fma(blkaik, blkb, blkc);
                simdlib::store_aligned(crowi, blkc);
            }
#endif
        }
    }
}
}

#endif
