#include <iostream>
#include <cmath>
#include <limits>

auto f(double x) -> double
{
    return sin(x) * sin(x) + cos(x) * cos(x) - 1.0;
}

auto main() -> int
{
    auto npoints { 1000'000UL };
    auto pi { std::acos(-1) };
    auto eps { std::numeric_limits<double>::epsilon() };

    bool invalidated = false;
    for (auto i = 0UL; i < npoints; ++i) {
        double x{ 2 * pi * i / npoints };
        if (std::fabs(f(x)) > eps) {
            invalidated = true;
            break;
        }
    }
    if (invalidated) {
        std::cout << "There relation was found to be invalid.\n";
    } else {
        std::cout << "The relation was found to be valid for all points.\n";
    }
}

