#include <atomic>
#include <cmath>
#include <iostream>
#include <numbers>
#include <thread>

auto main() -> int
{
    using std::numbers::pi;
    constexpr auto N = 1'000'000UL;
    std::atomic<double> tot {};
    {
        std::jthread j1 { [&]() {
            for (auto i = 0UL; i < N; ++i) {
                auto ang = 2 * i * pi / N;
                tot += std::cos(ang) * std::cos(ang);
            }
        } };
        std::jthread j2 { [&]() {
            for (auto i = 0UL; i < N; ++i) {
                auto ang = 2 * i * pi / N;
                tot += std::sin(ang) * std::sin(ang);
            }
        } };
    }
    std::cout << "Total " << tot << "\n";
}
