// examples/trig_views.cc
#include <iostream>
#include <ranges>
#include <algorithm>
#include <cmath>
#include <limits>

int main()
{
    namespace sr = std::ranges;
    namespace sv = std::views;
    const auto pi = std::acos(-1);
    constexpr auto npoints = 10'000'00UL;
    constexpr auto eps = 100 * std::numeric_limits<double>::epsilon();
    auto is_bad = [=](double x){ return std::fabs(x) > eps; };
    auto res = sv::iota(0UL, npoints)
               | sv::transform([=](auto idx){ return std::lerp(0., 2*pi, idx * 1.0 / npoints); } )
               | sv::transform([ ](auto x)  { return sin(x) * sin(x) + cos(x) * cos(x) - 1.0;  } );
    if (sr::any_of(res, is_bad) ) {
        std::cerr << "There is at least one input for which the relation does not hold.\n"
                  << "They are...\n";
        for (auto bad_res : res | sv::filter(is_bad)) {
            std::cerr << bad_res << "\n";
        } 
    } else {
        std::cout << "The relation holds for all inputs\n";
    }
}


