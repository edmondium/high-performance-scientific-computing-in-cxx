// examples/trig_views.cc
#include <iostream>
#include <algorithm>
#include <cmath>
#include <limits>

#include <cxx20ranges>

// Compatibility header in your include path
// Replace with <ranges> if you only work with
// g++ or if your version of clang++ already
// has ranges algorithms implemented.

int main()
{
//    namespace sr = std::ranges;
//    namespace sv = std::views;
//  Uncomment the above two lines if you are not using the
//  compatibility header above.

    const auto pi = std::acos(-1);
    constexpr auto npoints = 10'000'00UL;
    constexpr auto eps = 100 * std::numeric_limits<double>::epsilon();
    auto to_0_2pi = [=](size_t idx) -> double {
         return std::lerp(0., 2*pi, idx * 1.0 / npoints);
    };
    auto x_to_fx = [ ](double x) -> double {
         return sin(x) * sin(x) + cos(x) * cos(x) - 1.0;
    };
    auto is_bad = [=](double x){ return std::fabs(x) > eps; };
    auto res = sv::iota(0UL, npoints) | sv::transform(to_0_2pi)
               | sv::transform(x_to_fx);
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


