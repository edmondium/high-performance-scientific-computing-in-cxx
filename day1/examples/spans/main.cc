#include <vector>
#include <valarray>
#include <iostream>
#include "spanfunc.hh"

using std::span;
void elsewhere(double* x, double* y,
               unsigned N)
{
    // Use it when you only have C-style
    // pointers and sizes
    std::cout << "adapting C-style arrays: "
              << compute(span(x, N), span(y, N)) << "\n";
}

auto main() -> int
{
    std::vector x(100UL, 2.3);
    std::vector y(x.size(), 3.4);
    // Use it as if it was written for vector!
    std::cout << "direct: " << compute(x, y) << "\n";
    std::valarray z(2.3, x.size()); // weird constructor, remember!
    // Use the same function also for valarrays!
    std::cout << "two valarrays: " << compute(z, z) << "\n";
    // Even with a valarray and a vector!
    std::cout << "valarray and vector : " << compute(x, z) << "\n";
    elsewhere(x.data(), y.data(), x.size());
}

