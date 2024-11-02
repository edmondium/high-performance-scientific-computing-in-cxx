#include "xsimd/xsimd.hpp"
#include <span>
#include <iostream>
#include <vector>

struct daxpy_xsimd_t {
template <class Arch>
void operator()(Arch, std::span<const double> x,
                   std::span<double> y, double a) const
{
    using b_type = xsimd::batch<double, Arch>;

    b_type bx{}, by{};
    const b_type ba{b_type::broadcast(a)};
    auto bsize = b_type::size;
    unsigned long vsize = x.size() - x.size() % bsize;
    const double * xptr0 = x.data();
    const double * xptr1 = x.data() + vsize;
    double * yptr = y.data();
    for (; xptr0 != xptr1; xptr0 += bsize, yptr += bsize) {
        bx = b_type::load_unaligned(xptr0);
        by = b_type::load_unaligned(yptr);
        by = by + bx * ba;
        by.store_unaligned(yptr);
    }
    for (auto i = vsize; i < x.size(); ++i) {
        y[i] = a * x[i] + y[i];
    }
}
};
inline auto daxpy_xsimd = xsimd::dispatch(daxpy_xsimd_t{});

auto main() -> int
{
    std::vector v1(1000'000'0UL, 2.3);
    std::vector v2(1000'000'0UL, 3.3);
    daxpy_xsimd(v1, v2, 1.2);
    std::cout << v2[223] << "\n";
}

