#pragma once

#include <chrono>
#include <cmath>
#include <iostream>
#include <string_view>

template <typename Callable, typename... Args>
void timeit(std::string_view testname, unsigned reps, Callable&& f, Args&&... args)
{
    using namespace std::chrono;
    double tmin {}, tmax {}, ttot {}, t2tot {};
    for (auto i = 0u; i < reps; ++i) {
        auto start = high_resolution_clock::now();
        std::forward<Callable>(f)(std::forward<Args>(args)...);
        auto end = high_resolution_clock::now();
        auto intv = duration<double>(end - start).count();
        if (i == 0u) {
            tmin = tmax = intv;
        } else {
            tmax = std::max(tmax, intv);
            tmin = std::min(tmin, intv);
        }
        ttot += intv;
        t2tot += (intv * intv);
    }
    enum class TUnit { sec,
        msec,
        usec,
        nsec };
    TUnit u = TUnit::sec;
    if (tmin < 1.0)
        u = TUnit::msec;
    if (tmin < 1.e-3)
        u = TUnit::usec;
    if (tmin < 1.e-6)
        u = TUnit::nsec;
    double tmean = ttot / reps;
    double t2mean = t2tot / reps;
    double tstdv = sqrt(t2mean - tmean * tmean);
    std::string unitstring { " seconds" };
    double conv { 1.0 };
    switch (u) {
    case TUnit::msec:
        unitstring = " milliseconds";
        conv = 1000.0;
        break;
    case TUnit::usec:
        unitstring = " microseconds";
        conv = 1000000.0;
        break;
    case TUnit::nsec:
        unitstring = " nanoseconds";
        conv = 1000000000.0;
        break;
    case TUnit::sec:
    default:
        break;
    };
    std::cout << "Timing results for " << testname << " from " << reps << " repititions...\n";
    std::cout << "Mean = " << tmean * conv << unitstring << "\n";
    std::cout << "Std. dev = " << tstdv * conv << unitstring << "\n";
    std::cout << "Minimum = " << tmin * conv << unitstring << "\n";
    std::cout << "Maximum = " << tmax * conv << unitstring << "\n";
}
