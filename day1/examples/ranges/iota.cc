// examples/iota.cc
#include <iostream>
#include <ranges>

auto main() -> int
{
    namespace sv = std::ranges::views;
    for (auto i : sv::iota(1UL)) {
        if ((i + 1) % 10000UL == 0UL) {
            std::cout << i << ' ';
            if ((i + 1) % 100000UL == 0UL)
                std::cout << '\n';
            if (i >= 100000000UL)
                break;
        }
    }
}
