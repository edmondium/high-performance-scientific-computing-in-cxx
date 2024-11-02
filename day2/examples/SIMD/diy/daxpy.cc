#include "QuadDouble.hh"
#include <vector>

void daxpy_explicit(const std::vector<double> & x,
                   std::vector<double> & y, double a)
{
    QuadDouble bx{0.}, by{0.};
    const QuadDouble ba{a};
    unsigned long vsize = x.size() - x.size() % 4;
    const double * xptr0 = x.data();
    const double * xptr1 = x.data() + vsize;
    double * yptr = y.data();
    for (; xptr0 != xptr1; xptr0 += 4, yptr += 4) {
        bx.unaligned_load(xptr0);
        by.unaligned_load(yptr);
        by = by + bx * ba;
        by.unaligned_store(yptr);
    }
    for (auto i = vsize; i < x.size(); ++i) {
        y[i] = a * x[i] + y[i];
    }
}


