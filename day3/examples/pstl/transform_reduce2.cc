#include <execution>
#include <iostream>
#include <numeric>
#include <vector>
#include <chrono>
#include <random>

auto random_number_generator() -> double
{
    // usage of thread local random engines allows running the generator in concurrent mode
    thread_local static std::default_random_engine rd;
    std::uniform_real_distribution<double> dist(-1.0, 1.0);
    return dist(rd);
}


auto main() -> int
{
    constexpr auto N = 100'000'000UL;
    std::vector x(N, 1.0), y(N, 1.0);
    std::cout << "Filling up 2 arrays of size " << N << " with random numbers\n";
    std::generate(std::execution::par, x.begin(), x.end(), random_number_generator);
    std::generate(std::execution::par, y.begin(), y.end(), random_number_generator);
    std::cout << "Random number filling done.\n";
    auto res1 = std::reduce(std::execution::par, x.begin(), x.end(), 0.);
    std::cout << "Reduction done.\n";
    std::atomic<double> res2;
    std::for_each(std::execution::par, x.begin(), x.end(), 
		    [&](auto X) { res2 += X; });
    std::cout << "reduce() : " << res1 << "\n";
    std::cout << "atomic<double> : " << res2 << "\n";
}
