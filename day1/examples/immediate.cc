#include <iostream>
#include <array>
#include <ranges>
#include <algorithm>
#include <iterator>

template <class T> consteval auto sqr(T x) { return x*x; }

auto main(int argc, char* argv[]) -> int
{
    std::array<double, sqr(11)> A;
    A.fill(1.1);

    std::ranges::copy(A, std::ostream_iterator<double>(std::cout, ", "));
    std::cout << "\n";
    std::cout << "Square of 33 is " << sqr(33) << "\n";
    //std::cout << "Square of the number of arguments is " << sqr(argc) << "\n";
}

