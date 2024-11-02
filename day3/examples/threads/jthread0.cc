#include <cmath>
#include <iostream>
#include <numbers>
#include <thread>

auto main() -> int
{
    using std::numbers::pi;
    constexpr auto N = 1'000'000UL;
    std::jthread j1 { [=]() {
        auto tot1 = 0.;
        for (auto i = 0UL; i < N; ++i) {
            auto ang = 2 * i * pi / N;
            tot1 += std::cos(ang) * std::cos(ang);
        }
        std::cout << "Thread 1 got total " << tot1 << "\n";
    } };
    std::jthread j2 { [=]() {
        auto tot2 = 0.;
        for (auto i = 0UL; i < N; ++i) {
            auto ang = 2 * i * pi / N;
            tot2 += std::sin(ang) * std::sin(ang);
        }
        std::cout << "Thread 2 got total " << tot2 << "\n";
    } };
}
