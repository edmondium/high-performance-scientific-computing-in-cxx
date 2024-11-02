#include <format>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

auto main() -> int
{
    namespace sv = std::ranges::views;
    using namespace std::literals;
    std::vector v { "apples"s, "oranges"s, "mangos"s, "bananas"s };

    for (auto [i, fruit] : sv::enumerate(v)) {
        std::cout << format("{}: {}\n", i, fruit);
    }
}
