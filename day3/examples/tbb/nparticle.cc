#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
//#include <tbb/concurrent_vector.h>
//#include <tbb/concurrent_vector.h>
//#include <tbb/enumerable_thread_specific.h>
//#include <tbb/tbb.h>

struct particle_data {
    double x, y, z, q;
};
//using data_array = tbb::concurrent_vector<particle_data>;
using data_array = std::vector<particle_data>;
constexpr inline double sqr(double x) { return x * x; }

template <typename InputIterator>
auto e_rng(InputIterator i0, InputIterator i1, InputIterator j0, InputIterator j1) -> double
{
    double etmp = 0;
    for (auto i = i0; i < i1; ++i) {
        for (auto j = j0; j < j1; ++j) {
            if (j > i) {
                double r2 = sqr(i->x - j->x) + sqr(i->y - j->y) + sqr(i->z - j->z);
                etmp += i->q * j->q / sqrt(r2);
            }
        }
    }
    return etmp;
}

// Insert the TBB parallel version with blocked_range2d here
////////////////////////////////////////////////////////////

auto main() -> int
{
    std::mt19937_64 engine;
    std::uniform_real_distribution<> dist{ -5, 5 };
    auto gen = [&] { return dist(engine); };
    constexpr size_t N = 50000;
    data_array P(N);

    std::cout << "Filling up coordinate arrays with random numbers serially\n";
    auto t0 = std::chrono::high_resolution_clock::now();
    for (auto& p : P) {
        p.x = gen();
        p.y = gen();
        p.z = gen();
        p.q = 0.1;
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << "Filling particle array took : "
              << std::chrono::duration<double>(t1 - t0).count() << " seconds\n";

    std::cout << "Serial energy evaluation ...\n";
    t0 = std::chrono::high_resolution_clock::now();
    double eser = e_rng(P.begin(), P.end(), P.begin(), P.end());
    t1 = std::chrono::high_resolution_clock::now();
    auto tser = std::chrono::duration<double>(t1 - t0).count();
    std::cout << "Serial energy evaluation took : " << tser << " seconds\n";
    std::cout << "Serial calculation result = " << eser << "\n";
    // Once you have filled in the TBB parallel version of e_par
    // above, you can uncomment the following lines
    // std::cout << "Parallel energy evaluation ...\n";
    // t0 = std::chrono::high_resolution_clock::now();
    // double epar = e_par(P.begin(), P.end(), P.begin(), P.end());
    // t1 = std::chrono::high_resolution_clock::now();
    // auto tpar = std::chrono::duration<double>(t1 - t0).count();
    // std::cout << "Parallel energy evaluation took : " << tpar << " seconds\n";
    // std::cout << "Total error = " << fabs(eser - epar) << '\n';
    // std::cout << "Speed up in TBB version relative to serial version = " << 100 * tser / tpar << "\n";
}
