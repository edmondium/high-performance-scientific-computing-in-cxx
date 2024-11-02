#include <iostream>
#include <numeric>

auto main() -> int
{
    auto x = 2147483645, y = 2147483641

    std::cout << "Mid-point of " << x << " and " << y << " is " 
              << std::midpoint(x, y) << "\n"

    std::cout << "Naive mid-point of " << x << " and " << y << " is " 
              << (x + y)/2 << "\n"
}

