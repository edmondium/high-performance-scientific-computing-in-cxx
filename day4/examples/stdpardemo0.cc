#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <execution>


auto main() -> int
{
    constexpr auto N = 10000000UL;
    std::vector vals(N, 0.);
    std::mt19937_64 engine{ std::random_device{}() };
    std::uniform_real_distribution<> dist{-1.0, 1.0};

    std::generate(vals.begin(), vals.end(), [=]()mutable { return dist(engine); });

    std::sort(std::execution::par, vals.begin(), vals.end());
    std::cout << "Middle element after sort = " << vals[N/2] << "\n";
}

