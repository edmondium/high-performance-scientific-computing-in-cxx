#include "spanfunc.hh"
#include <numeric>
#include <functional>

using std::span;
using std::transform_reduce;
using std::plus;
using std::multiplies;
// write function in terms of spans
auto compute(span<const double> u,
    span<const double> v) -> double
{
    return transform_reduce(
        u.begin(), u.end(),
        v.begin(), 0., plus<double>{},
        multiplies<double>{});
}
