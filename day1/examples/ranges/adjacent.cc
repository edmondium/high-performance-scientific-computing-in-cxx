#include <print>
#include <ranges>

auto main() -> int
{
    namespace sv = std::ranges::views;
    for (auto [i0, i1, i2]:
	    sv::iota(0UL, 15UL) | sv::adjacent<3UL>) {
        std::print("{}, {}, {}\n", i0, i1, i2);
    }
}

