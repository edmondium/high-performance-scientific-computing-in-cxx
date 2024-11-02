#include <iostream>
#include <vector>
#include <ranges>
#include <cxx20format>

auto main() -> int
{
    namespace sr = std::ranges;
    namespace sv = sr::views;
    for (auto [i0, i1, i2]:
	    sv::iota(0UL, 15UL) | sv::adjacent<3UL>) {
        std::cout << format("{}, {}, {}\n", i0, i1, i2);
    }
}

