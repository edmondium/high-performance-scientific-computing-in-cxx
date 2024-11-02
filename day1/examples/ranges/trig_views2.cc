// examples/trig_views2.cc
#include <iostream>
#include <cxx20ranges>
#include <algorithm>
#include <cmath>
#include <limits>

auto main() -> int
{
    //namespace sr = std::ranges;
    //namespace sv = std::views;
    const auto pi = std::acos(-1);
    constexpr auto npoints = 100UL;
    auto is_bad = [=](double x){ return x > 0; };
    auto res = sv::iota(0UL, npoints)
               | sv::transform([=](auto idx){ 
                                   auto output =  std::lerp(0., 2*pi, idx * 1.0 / npoints);
                                   std::cout << "Mapping " << idx << " to " << output << "\n";
                                   return output;
                               } )
               | sv::transform([ ](auto x)  { 
                                   auto output = sin(x) * sin(x) - 0.99;
                                   std::cout << "Input = " << x << "\toutput = " << output << "\n"; 
                                   return output;
                               } );
    std::cout << "Evaluating any_of ...\n";
    if (sr::any_of(res, is_bad) ) {
        std::cerr << "There is at least one input for which the relation does not hold.\n";
    } else {
        std::cout << "The relation holds for all inputs\n";
    }
}


