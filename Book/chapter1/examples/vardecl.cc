#include <iostream>
#include <complex>

auto main() -> int
{
    using namespace std::complex_literals;
    auto Z{ 1.22 + 3.991i };
    std::cout << Z << "\n";
}

