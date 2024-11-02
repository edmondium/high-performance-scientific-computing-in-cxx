#include <format>
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

    for (auto s : sv::zip_transform(
		    [](auto&& s1, auto&& s2) {
		        return format("{} <--> {}", s1, s2);
		    }, 
		    v, sv::reverse(v))) {
        std::cout << s << "\n";
    }
}
