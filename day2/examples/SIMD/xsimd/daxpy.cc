#include "xsimd/xsimd.hpp"
#include <span>
using Arch = xsimd::avx2;
void daxpy_explicit(std::span<const double> x,
                   std::span<double> y, double a)
{
    using btype = xsimd::batch<double, Arch>;
    const btype ba = btype::broadcast(a);
    unsigned long vsize = x.size() - x.size() % 4;
    const double * xptr0 = x.data();
    const double * xptr1 = x.data() + vsize;
    double * yptr = y.data();
    for (; xptr0 != xptr1; xptr0 += 4, yptr += 4) {
        //auto bx = btype::load_unaligned(xptr0);
        auto bx = btype::load(xptr0, xsimd::unaligned_mode{});
        auto by = btype::load_unaligned(yptr);
        by = by + bx * ba;
        by.store_unaligned(yptr);
    }
    for (auto i = vsize; i < x.size(); ++i) {
        y[i] = a * x[i] + y[i];
    }
}


