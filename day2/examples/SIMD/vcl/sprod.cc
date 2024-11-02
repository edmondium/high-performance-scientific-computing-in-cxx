#include "vectorclass.h"

auto prod_explicit(size_t n, const double x[],
                   const double y[]) -> double
{
    Vec4d bx{0.}, by{0.}, tot{0.};
    unsigned long vsize = n - n % 4;
    const double * xptr0 = x;
    const double * xptr1 = x + vsize;
    for (; xptr0 != xptr1; xptr0 += 4, y += 4) {
        bx.load(xptr0);
        by.load(y);
        tot = tot + bx * by;
    }
    auto res = horizontal_add(tot);
    for (auto i = vsize; i < n; ++i) {
        res += x[i] * y[i];
    }
    return res;
}

