#include <algorithm>
#include <chrono>
#include <execution>
#include <iostream>
#include <random>
#include <vector>

auto main() -> int
{
    auto gen = [dist = std::uniform_real_distribution<> { -50.0, 50.0 },
                   engine = std::mt19937_64 { std::random_device {}() }]() mutable { return dist(engine); };
    using namespace std::chrono;
    std::cout << "Sequencial sorting ...\n";
    for (size_t i = 10000UL; i <= 100'000'000UL; i *= 10UL) {
        std::cout << "Array size = " << i << "\n";
        std::vector v(i, 0.);
        std::cout << "Filing with random numbers ...\n"; 
        auto t0 = high_resolution_clock::now();
        std::generate(v.begin(), v.end(), gen);
        auto t1 = high_resolution_clock::now();
        std::cout << "Time to fill = " << duration_cast<milliseconds>(t1-t0).count() << " milliseconds\n";
        auto t2 = high_resolution_clock::now();
        std::sort(v.begin(), v.end());
        auto t3 = high_resolution_clock::now();
        std::cout << "Time taken to sort " << v.size() << " numbers = "
                  << std::chrono::duration_cast<milliseconds>(t3 - t2).count() << " milliseconds\n";
        std::cout << v[0] << "\n";
    }
    std::cout << "Parallel sorting ...\n";
    for (size_t i = 10000UL; i <= 100'000'000UL; i *= 10UL) {
        std::cout << "Array size = " << i << "\n";
        std::vector v(i, 0.);
        std::cout << "Filing with random numbers ...\n"; 
        auto t0 = high_resolution_clock::now();
        std::generate(v.begin(), v.end(), gen);
        auto t1 = high_resolution_clock::now();
        std::cout << "Time to fill = " << duration_cast<milliseconds>(t1-t0).count() << " milliseconds\n";
        auto t2 = high_resolution_clock::now();
        std::sort(std::execution::par, v.begin(), v.end());
        auto t3 = high_resolution_clock::now();
        std::cout << "Time taken to sort " << v.size() << " numbers = "
                  << std::chrono::duration_cast<milliseconds>(t3 - t2).count() << " milliseconds\n";
        std::cout << v[0] << "\n";
    }
}
