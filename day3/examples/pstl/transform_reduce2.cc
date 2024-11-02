#include <algorithm>
#include <chrono>
#include <execution>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>
#include <version>

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
    auto t0 = std::chrono::high_resolution_clock::now();
    std::generate(std::execution::par, x.begin(), x.end(), random_number_generator);
    std::generate(std::execution::par, y.begin(), y.end(), random_number_generator);
    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << "Random number filling done, in "
              << std::chrono::duration<double>(t1 - t0).count() << " seconds\n";
    std::cout << "std::reduce...\n";
    t1 = std::chrono::high_resolution_clock::now();
    auto res1 = std::reduce(std::execution::par, x.begin(), x.end(), 0.);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Reduction done, in " << std::chrono::duration<double>(t2 - t1).count()
              << " seconds\n";
    ;
#ifdef __cpp_lib_atomic_float
    std::atomic<double> res2{};
    std::cout << "std::for_each with std::atomic<double>...\n";
    t2 = std::chrono::high_resolution_clock::now();
    std::for_each(std::execution::par, x.begin(), x.end(),
        [&](auto&& X) { res2.fetch_add(X); });
    auto t3 = std::chrono::high_resolution_clock::now();
    std::cout << "Reduction using atomic<double> finished in "
              << std::chrono::duration<double>(t3 - t2).count() << " seconds\n";
    std::cout << "reduce() : " << res1 << "\n";
    std::cout << "atomic<double> : " << res2 << "\n";
#endif
}
