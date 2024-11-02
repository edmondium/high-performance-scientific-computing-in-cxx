// examples/range_for.cc
#include <bit>
#include <iostream>
#include <ranges>
#include <numeric>

auto main() -> int
{
    std::array A { 1, 2, 3, 4, 5 };
    for (auto a : A)
        std::cout << a << "\n";

    for (auto partialsum = 0; auto a : A) {
        partialsum = partialsum + a;
        std::cout << a << "\t" << partialsum << "\n";
    }

    for (auto day : { "Monday", "Tuesday", "Wednessday", "Thursday", "Friday" }) {
        std::cout << day << "\n";
    }

    namespace sv = std::views;
    for (auto i : sv::iota(71UL)) {
        std::cout << i << "\n";
        if (std::popcount(i) == 7)
            break;
    }
}
