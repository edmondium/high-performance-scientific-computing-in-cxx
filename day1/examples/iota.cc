#include <ranges>
#include <iostream>
 
auto main() -> int
{
    using namespace std::views;
    for (auto i : iota(1UL)) {
        if ((i+1) % 10000UL == 0UL) {
            std::cout << i << ' ';
            if ((i+1) % 100000UL == 0UL) 
                std::cout << '\n';
            if (i >= 100000000UL) break;
        }
    }
}

