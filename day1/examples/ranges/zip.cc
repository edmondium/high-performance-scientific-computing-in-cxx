#include <print>
#include <ranges>
#include <string>
#include <vector>

auto main() -> int
{
    namespace sr = std::ranges;
    namespace sv = sr::views;
    using namespace std::literals;
    std::vector v { "apples"s, "oranges"s, "mangos"s, "bananas"s };

    for (auto [fruit1, fruit2] : sv::zip(v, sv::reverse(v))) {
        std::print("{}: {}\n", fruit1, fruit2);
    }
}
