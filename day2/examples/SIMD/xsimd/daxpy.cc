#include "xsimd/xsimd.hpp"
#include <vector>

void daxpy_explicit(const std::vector<double> & x,
                   std::vector<double> & y, double a)
{
    xsimd::simd_type<double> bx{0.}, by{0.};
    const xsimd::simd_type<double> ba{a};
    unsigned long vsize = x.size() - x.size() % 4;
    const double * xptr0 = x.data();
    const double * xptr1 = x.data() + vsize;
    double * yptr = y.data();
    for (; xptr0 != xptr1; xptr0 += 4, yptr += 4) {
        bx.load_unaligned(xptr0);
        by.load_unaligned(yptr);
        by = by + bx * ba;
        by.store_unaligned(yptr);
    }
    for (auto i = vsize; i < x.size(); ++i) {
        y[i] = a * x[i] + y[i];
    }
}


