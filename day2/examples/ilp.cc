#include <chrono>
#include <iostream>
#include <string>

inline auto f(double x, unsigned long n) -> double
{
    double a[12]{ 1.001, 0.999, 1.001, 0.999, 1.001, 0.999, 1.001, 0.999, 1.001, 0.999, 1.001, 0.999 };
    for (auto i = 0ul; i < n; ++i) {
        for (unsigned i = 0u; i<12u; ++i) x *= a[i];
        /*
        double c[6];
        for (unsigned j = 0u; j < 6u; ++j)
            c[j] = a[j] * a[6 + j];
        for (unsigned j = 0u; j < 3u; ++j)
            c[j] *= c[3 + j];
        x *= c[0];
        c[1] *= c[2];
        x *= c[1];
        */
    }
    return x;
}

auto main(int argc, char* argv[]) -> int
{
    double x = argc > 1 ? std::stod(argv[1]) : 3.141;
    size_t N = argc > 3 ? std::stoul(argv[3]) : 100'00'00ul;
    size_t n = argc > 2 ? std::stoul(argv[2]) : 10;
    for (size_t j = 1ul; j <= n; ++j) {
        double y = 0.;
        auto t0 = std::chrono::high_resolution_clock::now();
        y += f(x, N);
        auto t1 = std::chrono::high_resolution_clock::now();
        auto timetaken = std::chrono::duration<double>(t1 - t0).count();
        std::cout << j << "\t" << timetaken << "\t" << (12 * N + 1) / timetaken / 1.0e9 << " GFlops \t" << y << "\n";
    }
}
