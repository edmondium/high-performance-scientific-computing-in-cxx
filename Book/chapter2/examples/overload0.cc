// examples/overload0.cc
#include <iostream>
#include <cmath>
#include <limits>

auto power(double x, int n) -> double
{
    if (n == 0) return 1.;
    else if (n < 0) return 1.0/power(x, -n);
    auto ans{1.};
    while (n--) ans *= x;
    std::cout << "Using a simple loop to calculate power\n";
    return ans;
}

auto power(double x, double y) -> double
{
    std::cout << "Using exp of log method to calculate power\n";
    if (x < 0) {
        std::cerr << "Invalid input for non-integral power function: " << x << "\n";
        exit(1);
    } else if (x == 0) {
        if (y > 0) return 0.;
        else if (y < 0) return std::numeric_limits<double>::infinity();
        else return std::numeric_limits<double>::quiet_NaN();
    } else return std::exp(y * std::log(x));
}

auto main() -> int
{
    std::cout << power(4.0, 3) << "\n\n";
    std::cout << power(4.0, 3.) << "\n\n";
}

