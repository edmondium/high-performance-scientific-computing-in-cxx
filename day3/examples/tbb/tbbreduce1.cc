#include <chrono>
#include <cmath>
#include <iostream>
#include <tbb/enumerable_thread_specific.h>
#include <tbb/tbb.h>
#include <vector>

inline auto f(double x) -> double
{
    return tanh(x) * cos(x) * sin(x);
}

auto main() -> int
{
    constexpr double llim = 10.;
    constexpr double ulim = 120.;
    constexpr double dx = 1.0e-6;
    size_t N = (size_t)(ulim - llim) / dx;
    std::cout << "Starting serial computation.\n";
    auto t0 = std::chrono::high_resolution_clock::now();
    double ans_ser = [llim, dx, N] {
        double tmp = 0;
        for (size_t i = 0; i < N; ++i)
            tmp += f(llim + i * dx) * dx;
        return tmp;
    }();
    std::cout << "Integral with single thread = " << ans_ser << '\n';
    auto t1 = std::chrono::high_resolution_clock::now();
    auto tser = std::chrono::duration<double>(t1 - t0).count();
    std::cout << "Serial computation took " << tser << '\n';
    auto t2 = std::chrono::high_resolution_clock::now();
    tbb::enumerable_thread_specific<double> S;
    tbb::parallel_for(tbb::blocked_range<size_t>(0, N), [&](tbb::blocked_range<size_t> r) {
        auto& s = S.local();
        for (auto i = r.begin(); i != r.end(); ++i)
            s += f(llim + i * dx) * dx;
    });
    double sum = 0;
    for (auto& s : S)
        sum += s;

    std::cout << "Integral = " << sum << '\n';
    auto t3 = std::chrono::high_resolution_clock::now();
    auto tpar = std::chrono::duration<double>(t3 - t2).count();
    std::cout << "Parallel computation took " << tpar << '\n';
    std::cout << "Observed speedup vs serial = " << 100.0 * tser / tpar << " %\n";
}
