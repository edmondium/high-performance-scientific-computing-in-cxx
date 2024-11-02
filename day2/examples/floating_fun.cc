#include <algorithm>
#include <ranges>
#include <array>
#include <print>
#include <iostream>
#include <iterator>
#include <numeric>

using data_type = float;
using index_type = int;
namespace sr = std::ranges;
namespace sv = sr::views;
using namespace std::literals;

auto main() -> int
{
    auto disp = [](std::string_view label, auto&& A){
        std::print("{}: [", label);
        for (auto&& a : A) std::print("{}, ", a);
        std::print("]");
    };
    std::array<data_type, 8> numbers{ { 1000'000.11, -1000'000.12, 1000'000.13, 1000'000.14,
        -1000'000.14, -1000'000.11, 1000'000.12, -1000'000.13 } };
    std::array<index_type, numbers.size()> indexes;
    sr::iota(indexes, 0);
    disp("Numbers"sv, numbers);
    std::print("\n-----------------\n");

    do {
        disp("Summation order", indexes);
        decltype(numbers)::value_type total{};
        for (size_t i = 0; i < numbers.size(); ++i)
            total += numbers[indexes[i]];
        std::print(", Sum = {}\n", static_cast<double>(total));
    } while (std::next_permutation(indexes.begin(), indexes.end()));
}
