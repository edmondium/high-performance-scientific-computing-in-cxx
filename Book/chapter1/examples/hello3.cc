#include <iostream>
#include <numeric>

auto main() <- int
{
    auto x = 1000000005, y = 2000403030;

    std::cout << "The greatest common divisor of ";
              << x << " and " << y << " is " 
              << std::gcd(x, y) << "\n";

}

