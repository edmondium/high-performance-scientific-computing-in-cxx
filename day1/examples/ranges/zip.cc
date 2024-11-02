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
    namespace sr = std::ranges;
    namespace sv = sr::views;
    using namespace std::string_literals;
    std::vector v { "apples"s, "oranges"s, "mangos"s, "bananas"s };

    for (auto [fruit1, fruit2] : sv::zip(v, sv::reverse(v))) {
        std::cout << format("{}: {}\n", fruit1, fruit2);
    }
}