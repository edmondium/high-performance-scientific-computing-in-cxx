#include <chrono>
#include <print>
#include <span>
#include <string>

inline auto f(double xx, unsigned long n, std::span<volatile double> a) -> double
{
    volatile double x { xx };
    for (auto i = 0UL; i < n; ++i) {
        // Inner loop, version 1
/*
        for (auto j = 0UL; j < a.size(); ++j)
            x = x * a[j];
*/

        // Inner "loop", version 2
        {
            double c[6];
            for (unsigned j = 0u; j < 6u; ++j)
                c[j] = a[j] * a[6 + j];
            for (unsigned j = 0u; j < 3u; ++j)
                c[j] *= c[3 + j];
            x = x * c[0];
            c[1] *= c[2];
            x = x * c[1];
        }
    }
    return x;
}

auto main(int argc, char* argv[]) -> int
{
    double x = argc > 1 ? std::stod(argv[1]) : 3.141;
    size_t N = argc > 3 ? std::stoul(argv[3]) : 100'00'00ul;
    size_t n = argc > 2 ? std::stoul(argv[2]) : 10;
    double a[12] { 1.001, 0.999, 1.001, 0.999, 1.001, 0.999, 1.001, 0.999, 1.001, 0.999, 1.001, 0.999 };
    for (size_t j = 1UL; j <= n; ++j) {
        double y = 0.;
        auto t0 = std::chrono::high_resolution_clock::now();
        y += f(x, N, { a });
        auto t1 = std::chrono::high_resolution_clock::now();
        auto timetaken = std::chrono::duration<double>(t1 - t0).count();
        std::print("{:<8}\t{:>10.8f}\t{:>8.2f} GFlops, tot = {}\n",
            j, timetaken, (12 * N + 1) / timetaken / 1.0e9, y);
    }
}
