// examples/trig_valarray.cc

#include <iostream>
#include <cmath>
#include <limits>
#include <ranges>
#include <valarray>

auto linspace(double min, double max, unsigned long howmany)
    -> std::valarray<double>
{
    std::valarray answer(0., howmany);
    for (auto i = 0UL; i < howmany; ++i) {
        answer[i] = min + (max - min) * i / howmany; 
    }
    return answer;
}

auto main() -> int
{
    constexpr auto npoints { 1000'000UL };
    const auto pi { std::acos(-1) };
    constexpr auto eps { std::numeric_limits<double>::epsilon() };

    const std::valarray X = linspace(0., 2 * pi, npoints);
    const std::valarray res = sin(X) * sin(X) + cos(X) * cos(X) - 1;

    if (std::ranges::any_of(res, [](double x)->bool{ return std::fabs(x) > eps;} )) {
        std::cout << "There relation was found to be invalid.\n";
    } else {
        std::cout << "The relation was found to be valid for all points.\n";
    }
}


