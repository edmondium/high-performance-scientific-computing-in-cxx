// examples/math_functions.cc
#include <cmath>
#include <iostream>
auto main() -> int
{
    double inp = 3.141592653 / 6.0;
    //
    std::cout << "Enter angle: ";
    //
    std::cin >> inp;
    std::cout << "sqrt(" << inp << ") = " << std::sqrt(inp) << "\n";
    std::cout << "cbrt(" << inp << ") = " << std::cbrt(inp) << "\n";
    std::cout << "cos(" << inp << ") = " << std::cos(inp) << "\n";
    std::cout << "sin(" << inp << ") = " << std::sin(inp) << "\n";
    std::cout << "cosh(" << inp << ") = " << std::cosh(inp) << "\n";
    std::cout << "sinh(" << inp << ") = " << std::sinh(inp) << "\n";
    std::cout << "exp(" << inp << ") = " << std::exp(inp) << "\n";
    std::cout << "erf(" << inp << ") = " << std::erf(inp) << "\n";
    std::cout << "riemann_zeta(" << inp << ") = " << std::riemann_zeta(inp) << "\n";
}
