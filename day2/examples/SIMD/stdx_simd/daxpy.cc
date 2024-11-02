#include <vector>
#include <span>
#include <experimental/simd>

namespace stdx = std::experimental;
using DataType = double;
using b_type = stdx::native_simd<DataType>;

void daxpy_explicit(std::span<const DataType> x,
                   std::span<DataType> y, DataType a)
{
    const auto bsize = b_type::size();
    stdx::native_simd<DataType> bx{0.}, by{0.};
    const stdx::native_simd<DataType> ba{a};
    unsigned long vsize = x.size() - x.size() % bsize;
    const DataType * xptr0 = x.data();
    const DataType * xptr1 = x.data() + vsize;
    DataType * yptr = y.data();
    for (; xptr0 != xptr1; xptr0 += bsize, yptr += bsize) {
        bx.copy_from(xptr0, stdx::element_aligned);
        by.copy_from(yptr, stdx::element_aligned);
        by = by + bx * ba;
        by.copy_to(yptr, stdx::element_aligned);
    }
    for (auto i = vsize; i < x.size(); ++i) {
        y[i] = a * x[i] + y[i];
    }
}

auto main() -> int
{
    constexpr auto N = 1000000UL;
    std::vector<double> X(N, 2.3);
    std::vector<double> Y(N, 2.3);
    daxpy_explicit(X, Y, 5.);
    return static_cast<int>(Y[N/2UL]);
}


