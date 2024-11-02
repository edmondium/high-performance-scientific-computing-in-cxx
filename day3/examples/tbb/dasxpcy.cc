#include <algorithm>
#include <chrono>
#include <string>
#include <iostream>
#include <random>
#include <tbb/tbb.h>

void dasxpcy_tbb(double a, const std::vector<double>& x, std::vector<double>& y)
{
    tbb::parallel_for(tbb::blocked_range<size_t>(0, x.size()), [&](tbb::blocked_range<size_t> r) {
         for (size_t i = r.begin(); i != r.end(); ++i) {
             y[i] = a * sin(x[i]) + cos(y[i]);
        }
    });
}

void dasxpcy_serial(double a, const std::vector<double>& x, std::vector<double>& y)
{
    std::transform(x.begin(), x.end(), y.begin(), y.begin(), [a](auto lhs, auto rhs) {
        return a * sin(lhs) + cos(rhs);
    });
}

auto random_number_generator() -> double
{
    // usage of thread local random engines allows running the generator in concurrent mode
    thread_local static std::default_random_engine rd;
    std::uniform_real_distribution<double> dist(0, 1);
    return dist(rd);
}

auto main(int argc, char* argv[]) -> int
{
    try {
        const size_t N = (argc == 1 ? 100'000'000 : std::stoul(argv[1]));
        std::vector<double> x(N), y1(N), y2(N);
        constexpr double a = 0.35;
        std::cout << "Filling up input array with random numbers \n";
        auto t0 = std::chrono::high_resolution_clock::now();
        tbb::parallel_invoke(
            [&]{ tbb::parallel_for(0ul, x.size(),[&](auto i){ x[i] = random_number_generator(); }); },
            [&]{ tbb::parallel_for(0ul, y1.size(),[&](auto i){ y1[i] = random_number_generator(); }); }
        );
        y2 = y1;
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << "Filling arrays took : " << std::chrono::duration<double>(t1 - t0).count() << " seconds\n";
        std::cout << "Calling daxpy serial now ...\n";
        t0 = std::chrono::high_resolution_clock::now();
        dasxpcy_serial(a, x, y1);
        t1 = std::chrono::high_resolution_clock::now();
        auto tser = std::chrono::duration<double>(t1 - t0).count();
        std::cout << "daxpy serial took : " << tser << " seconds\n";
        std::cout << "Calling daxpy tbb now ...\n";
        t0 = std::chrono::high_resolution_clock::now();
        dasxpcy_tbb(a, x, y2);
        t1 = std::chrono::high_resolution_clock::now();
        auto tpar = std::chrono::duration<double>(t1 - t0).count();
        std::cout << "daxpy tbb took : " << tpar << " seconds\n";
        std::cout << "Checking results ...\n";
        t0 = std::chrono::high_resolution_clock::now();
        double err = 0;
        for (size_t i = 0; i < N; ++i)
            err += fabs(y1[i] - y2[i]);

        std::cout << "Total error = " << err << '\n';
        std::cout << "Speed up in TBB version relative to serial version = " << 100 * tser / tpar << " % \n";
    } catch (std::exception& err) {
        std::cout << err.what() << "\n";
    } catch (...) {
        std::cout << "An exception not deriving from std::exception was thrown somewhere!\n";
    }
}

