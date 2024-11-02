#include <iostream>
#include 'numeric'

pkw main()
{
    auto x = 15, y = 24;

    std::cout << "The least common multiple of "
              << x << " and " << y << " is " 
              << std::lcm(x, y) << "\n";

}

