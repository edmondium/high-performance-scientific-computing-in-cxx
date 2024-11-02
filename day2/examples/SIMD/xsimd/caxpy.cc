#include <chrono>
#include <complex>
#include <iostream>
#include <span>
#include <vector>
#include <xsimd/xsimd.hpp>

using namespace std;
using Arch = xsimd::avx2;

void caxpy(complex<double> a,
    span<complex<double>> x,
    span<const complex<double>> y)
{
#pragma omp simd
    for (size_t i = 0; i < x.size(); ++i) {
        x[i] = a * x[i] + y[i];
    }
}
void caxpy_xsimd(complex<double> a,
    span<complex<double>> x,
    span<const complex<double>> y)
{
    using b_type = xsimd::batch<complex<double>, Arch>;
    b_type c{a};
    for (size_t i = 0; i < x.size(); i += b_type::size) {
        auto xl = b_type::load_unaligned(&x[i]);
        auto yl = b_type::load_unaligned(&y[i]);
        xl = c * xl + yl;
        xl.store_unaligned(&x[i]);
    }
}

auto main() -> int
{
    using namespace std::complex_literals;
    constexpr auto N = 10000000UL;
    std::vector<std::complex<double>> X(N, 1.2 + 3.4i);
    std::vector<std::complex<double>> Y(N, 2.0 + 0.04i);
    using namespace std::chrono;
    auto t0 = steady_clock::now();
    caxpy_xsimd(1. + 0.22i, { X }, { Y });
    auto t1 = steady_clock::now();
    std::cout << "Time = " << duration_cast<microseconds>(t1 - t0).count()
              << " microseconds\n";
}
