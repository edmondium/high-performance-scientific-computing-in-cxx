#include "xsimd/xsimd.hpp"
#include <span>

using Arch = xsimd::avx2;

auto sprod_explicit(std::span<const double> x,
                   std::span<const double> y) -> double
{
    using b_type = xsimd::batch<double, Arch>;
    constexpr auto bsize = b_type::size;
    b_type tot{};
    unsigned long vsize = x.size() - x.size() % bsize;
    const auto* xptr0 = x.data();
    const auto* xptr1 = x.data() + vsize;
    const auto* yptr = y.data();
    for (; xptr0 != xptr1; xptr0 += bsize, yptr += bsize) {
        auto bx = b_type::load_unaligned(xptr0);
        auto by = b_type::load_unaligned(yptr);
        tot = tot + bx * by;
    }
    auto res = reduce_add(tot);
    for (auto i = vsize; i < x.size(); ++i) {
        res += x[i] * y[i];
    }
    return res;
}

