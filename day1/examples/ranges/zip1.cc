#include <ranges>
#include <print>
#include <string>
#include <vector>

auto main() -> int
{
    namespace sr = std::ranges;
    namespace sv = sr::views;
    using namespace std::literals;
    std::vector v { "apples"s, "oranges"s, "mangos"s, "bananas"s };

    for (auto&& [i, fruits] : sv::zip(v, sv::reverse(v)) | sv::enumerate) {
	auto&& [fruit1, fruit2] = fruits;
        std::print("{}: {} <-> {}\n", i, fruit1, fruit2);
    }
}
