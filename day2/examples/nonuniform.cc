#include <iostream>
#include <random>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    auto gen = [engine = std::mt19937_64(std::random_device {}()),
                   dist = std::exponential_distribution<> { 3.4 }]() mutable { return dist(engine); };
    auto N = (argc < 2 ? 10000UL : std::stoul(argv[1]));
    for (auto i = 0UL; i < N; ++i)
        std::cout << gen() << "\n";
}
