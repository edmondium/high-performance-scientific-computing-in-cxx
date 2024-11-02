#include "QuadDouble.hh"
#include <span>

auto sprod_explicit(std::span<const double> x,
    std::span<const double> y) -> double
{
    QuadDouble bx{0.}, by{0.}, tot{0.};
    unsigned long vsize = x.size() - x.size() % 4;
    const double * xptr0 = x.data();
    const double * xptr1 = x.data() + vsize;
    const double * yptr = y.data();
    for (; xptr0 != xptr1; xptr0 += 4, yptr += 4) {
        bx.unaligned_load(xptr0);
        by.unaligned_load(yptr);
        tot = tot + bx * by;
    }
    auto res = tot.horizontal_add();
    for (auto i = vsize; i < x.size(); ++i) {
        res += x[i] * y[i];
    }
    return res;
}

