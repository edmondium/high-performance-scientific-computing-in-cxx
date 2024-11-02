#include <experimental/simd>
#include <span>
#include <vector>
#include <iostream>

namespace stdx = std::experimental;

auto sprod_stdx(std::span<const double> x,
                   std::span<const double> y) -> double
{
    using b_type = stdx::native_simd<double>;
    constexpr auto bsize = b_type::size();
    b_type tot{}, bx{}, by{};
    unsigned long vsize = x.size() - x.size() % bsize;
    const auto* xptr0 = x.data();
    const auto* xptr1 = x.data() + vsize;
    const auto* yptr = y.data();
    for (; xptr0 != xptr1; xptr0 += bsize, yptr += bsize) {
        bx.copy_from(xptr0, stdx::element_aligned);
        by.copy_from(yptr, stdx::element_aligned);
        tot = tot + bx * by;
    }
    auto res = reduce(tot);
    for (auto i = vsize; i < x.size(); ++i) {
        res += x[i] * y[i];
    }
    return res;
}

auto main() -> int 
{
    constexpr auto N = 10000000UL;
    std::vector<double> A(N, 3.), B(N, 2.);

    std::cout << sprod_stdx(A, B) << "\n";
}

