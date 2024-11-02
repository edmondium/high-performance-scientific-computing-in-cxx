#include <xtensor/xtensor.hpp>
#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xrandom.hpp>
#include <xtensor-blas/xlinalg.hpp>
#include <iostream>
#include <chrono>

auto main(int argc, char* argv[]) -> int
{
    auto size = (argc > 1 ? std::stoul(argv[1]) : 1024);
    auto R1 = xt::random::rand<double>({size, size});
    auto R2 = xt::random::rand<double>({size, size});
    auto t0 = std::chrono::high_resolution_clock::now();
    auto R3 = xt::linalg::dot(R1,R2);
    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << R3 << "\n\n";
    auto t = std::chrono::duration<double>(t1-t0).count();
    std::cout << "Time taken = " << t << " seconds\n";
    std::cout << size * size * (2 * size -1) /t / 1.0e9 << " Gflops\n";
}

