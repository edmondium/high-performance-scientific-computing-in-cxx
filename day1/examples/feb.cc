/*
Calculates the years in a given interval, in which
the month of February had 5 Sundays.

Usage:
(i)   feb      # Start: current year, End: 100 years from now
(ii)  feb 1975 # Start: 1975, End: current year
(iii) feb 2075 # Start: current year, End: 2075
(iv)  feb 1800 2000 # Start 1800, End 2000

Build:
clang++ -std=c++23 -stdlib=libc++ feb.cc -o feb

*/

#include <chrono>
#include <iostream>

auto current_year() -> std::chrono::year
{
    using namespace std::chrono;
    year_month_day date { floor<days>(system_clock::now()) };
    return date.year();
}

auto main(int argc, char* argv[]) -> int
{
    using namespace std::chrono;
    using namespace std::chrono_literals;
    auto Y0 { current_year() };
    auto Y1 = Y0 + years { 100 };
    if (argc > 1)
        Y1 = year { std::stoi(argv[1]) };
    if (argc > 2)
        Y0 = year { std::stoi(argv[2]) };
    if (Y1 < Y0)
        std::swap(Y1, Y0);

    for (auto y = Y0; y < Y1; ++y) {
        auto d = y / February / Sunday[5];
        if (d.ok())
            std::cout << y << "\n";
    }
}
