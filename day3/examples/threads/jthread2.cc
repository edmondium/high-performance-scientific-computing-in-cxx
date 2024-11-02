#include <cmath>
#include <iostream>
#include <mutex>
#include <numbers>
#include <thread>
#include <vector>

auto main(int argc, char* argv[]) -> int
{
    using std::numbers::pi;
    constexpr auto N = 1'000'000UL;
    auto nthr = 10000UL;
    if (argc > 1)
        nthr = std::stoul(argv[1]);
    auto tot = 0.;
    std::mutex tot_mod_req;
    {
        std::vector<std::unique_ptr<std::jthread>> j1(nthr);
        std::vector<std::unique_ptr<std::jthread>> j2(nthr);
        auto lcos = [&]() {
            auto tmp = 0.;
            for (auto i = 0UL; i < N; ++i) {
                auto ang = 2 * i * pi / N;
                tmp += std::erfc(std::cos(ang) * std::cos(ang));
            }
            std::scoped_lock mod { tot_mod_req };
            tot += tmp;
        };
        auto lsin = [&]() {
            auto tmp = 0.;
            for (auto i = 0UL; i < N; ++i) {
                auto ang = 2 * i * pi / N;
                tmp += std::erfc(std::sin(ang) * std::sin(ang));
            }
            std::scoped_lock mod { tot_mod_req };
            tot += tmp;
        };
        for (auto& j : j1)
            j = std::make_unique<std::jthread>(lcos);
        for (auto& j : j2)
            j = std::make_unique<std::jthread>(lsin);
    }
    std::cout << "Total " << tot << "\n";
}
