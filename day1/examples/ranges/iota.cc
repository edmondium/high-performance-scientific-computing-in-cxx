// examples/iota.cc
#include <iostream>
#include <cxx20ranges>
// Compatibility header.

auto main() -> int
{
    // namespace sv = std::views;
    // Uncomment the line above if not using
    // the compatibility header.
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
