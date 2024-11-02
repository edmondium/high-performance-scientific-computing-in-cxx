#include <algorithm>
#include <array>
#include <print>
#include <ranges>
#include <iterator>
#include <iostream>

namespace sr = std::ranges;
namespace sv = sr::views;

template <class T>
consteval auto sqr(T x) { return x * x; }

auto main(int argc, char* argv[]) -> int
{
    std::array<double, sqr(11)> A;
    A.fill(1.1);
    sr::copy(A, std::ostream_iterator<double> {std::cout, ", "});
    std::print("\nSquare of 33 is {}\n", sqr(33));
    // std::print("\nSquare of the number of arguments is {}\n", sqr(argc));
}
