#include "xsimd/xsimd.hpp"

auto sprod_explicit(size_t n, const double x[],
                   const double y[]) -> double
{
    xsimd::simd_type<double> bx{0.}, by{0.}, tot{0.};
    unsigned long vsize = n - n % 4;
    const double * xptr0 = x;
    const double * xptr1 = x + vsize;
    for (; xptr0 != xptr1; xptr0 += 4, y += 4) {
        bx.load_unaligned(xptr0);
        by.load_unaligned(y);
        tot = tot + bx * by;
    }
    auto res = hadd(tot);
    for (auto i = vsize; i < n; ++i) {
        res += x[i] * y[i];
    }
    return res;
}

