#include <chrono>
#include <execution>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

auto main() -> int
{
    std::vector x(100'000'000, 1.0), y(100'000'000, 1.0);
    std::default_random_engine engine { std::random_device {}() };
    std::uniform_real_distribution<> dist { -10.0, 10.0 };
    auto gen = [&] { return dist(engine); };
    std::generate(x.begin(), x.end(), gen);
    std::generate(y.begin(), y.end(), gen);
    using namespace std::chrono;

    auto measure = [&](auto&& policy, std::string_view policyname) {
        std::cout << "New policy ... " << policyname << "\n";
        auto t0 = steady_clock::now();
        const auto a = 4.02;
        double result = std::transform_reduce(
            policy, x.begin(), x.end(), y.begin(), 0.0,
            std::plus<double> {},
            [a](auto X, auto Y) { return a * sin(X) * cos(Y); });
        std::cout << result << '\n';
        auto t1 = steady_clock::now();
        std::cout << "Time taken = "
                  << duration_cast<milliseconds>(t1 - t0).count()
                  << " milliseconds\n";
    };
    using namespace std::execution;
    measure(seq, "Sequenced execution policy");
    measure(unseq, "Unsequenced execution policy");
    measure(par, "Parallel execution policy");
    measure(par_unseq, "Parallel unsequenced execution policy");
}
