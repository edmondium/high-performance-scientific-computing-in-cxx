// Needs C++23. We don't have a sufficiently discerning
// redirecting header. So, we just include <ranges> and
// hope that the compiler has it. GCC 13.1 has an
// implementation.
#include <cxx20format>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>
#include <numbers>

auto main() -> int
{
    namespace sr = std::ranges;
    namespace sv = sr::views;
    using namespace std::string_literals;
    using namespace std::numbers;
    auto R = sv::iota(0UL, 50UL)
	    | sv::transform([](auto i) { return 2. * pi * i; })
            | sr::to<std::vector>();
    R.push_back(0.);
    for (auto x : R) {
        std::cout << x << "\n";
    }
}