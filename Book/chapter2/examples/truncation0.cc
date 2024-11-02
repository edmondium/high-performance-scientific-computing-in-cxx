// examples/truncation0.cc

#include <iostream>
#include "showbits.hh"
auto main() -> int
{
    auto x = 1.1111111e2F;
    auto y = 3.3333333e-2F;
    auto z = 1.1111111e2F;
    showbits(x);
    showbits(y);
    showbits(z);
    auto tot = x + y;
    std::cout << " x + y = " << tot << "\n";
    showbits(tot);
    tot = tot - z;
    std::cout << " x + y -z = " << tot << "\n";
    showbits(tot);
    tot = x - z;
    std::cout << " x - z = " << tot << "\n";
    showbits(tot);
    tot = tot + y;
    std::cout << " x -z + y= " << tot << "\n";
}

