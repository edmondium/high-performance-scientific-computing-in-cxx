// Needs C++23. We don't have a sufficiently discerning
// redirecting header. So, we just include <ranges> and
// hope that the compiler has it. GCC 13.1 has an
// implementation.
#include <cxx20format>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

auto main() -> int
{
    namespace sv = std::ranges::views;
    using namespace std::string_literals;
    std::vector v { "apples"s, "oranges"s, "mangos"s, "bananas"s };

    for (auto [i, fruit] : sv::enumerate(v)) {
        std::cout << format("{}: {}\n", i, fruit);
    }
}
