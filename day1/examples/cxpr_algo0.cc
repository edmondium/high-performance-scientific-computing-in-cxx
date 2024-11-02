#include <iostream>
#include <algorithm>
#include <array>
#include <ranges>

constexpr auto poly(double x) { return 3. * x * x * x - 2. * x * x + 0.877 * x - 1.0; }

constexpr auto bounds = []{
     std::array pre{ 1.2, 3.0, 0.99, 0.05, 1.44, 0.71, 0.881 };
     return std::ranges::minmax( pre | std::views::transform(poly) );
}();

int main()
{
    std::cout << bounds.min << "\t" << bounds.max << "\n";
    static_assert(bounds.min > -1. and bounds.min < -0.94);
}

