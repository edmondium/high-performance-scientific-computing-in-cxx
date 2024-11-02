#include <iostream>
#include <iomanip>
#include <utility>

auto main() -> int
{
    std::cout << "( -1 < 1U ) = " << std::boolalpha << ( -1 < 1U ) << "\n";
    std::cout << "std::cmp_less( -1 , 1U ) = " << std::boolalpha << std::cmp_less( -1 , 1U ) << "\n";
}

