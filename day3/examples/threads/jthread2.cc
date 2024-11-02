#include <cmath>
#include <iostream>
#include <mutex>
#include <numbers>
#include <thread>

auto main() -> int
{
    using std::numbers::pi;
    constexpr auto N = 1'000'000UL;
    auto tot = 0.;
    std::mutex totmutex;
    {
        std::jthread j1 { [&]() {
            for (auto i = 0UL; i < N; ++i) {
                auto ang = 2 * i * pi / N;
                std::scoped_lock lck { totmutex };
                tot += std::cos(ang) * std::cos(ang);
            }
        } };
        std::jthread j2 { [&]() {
            for (auto i = 0UL; i < N; ++i) {
                auto ang = 2 * i * pi / N;
                std::scoped_lock lck { totmutex };
                tot += std::sin(ang) * std::sin(ang);
            }
        } };
    }
    std::cout << "Total " << tot << "\n";
}
