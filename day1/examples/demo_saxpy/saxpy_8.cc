#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>
#include <vector>
#include <array>

namespace sr = std::ranges;
auto saxpy(std::floating_point auto a, 
           sr::input_range auto x, sr::input_range auto y, 
           std::weakly_incrementable auto&& z) -> void
{
    sr::transform(x, y, z, [a](auto X, auto Y) { return a * X + Y; });
} 

auto saxpy(std::weakly_incrementable auto&& z, std::floating_point auto a, 
           sr::input_range auto x, sr::input_range auto y) -> void
{
    sr::transform(x, y, z, [a](auto X, auto Y) { return a * X + Y; });
} 


auto main() -> int
{
    std::vector inp1 { 1., 2., 3., 4., 5. };
    std::vector inp2 { 9., 8., 7., 6., 5. };
    std::array  inp3 { 9., 8., 7., 6., 5. };
    double cstyle[]  { 1., 2., 3., 4., 5. };
    std::vector outp( inp1.size(), 0.);
    std::ostream_iterator<double> cout { std::cout, "\n" };
    saxpy(10., inp1, inp2, outp.begin());
    sr::copy(outp, cout);
    std::cout << ":::::::::::::::::::::\n";
    saxpy(10., inp1, inp3, outp.begin());
    sr::copy(outp, cout);
    std::cout << ":::::::::::::::::::::\n";
    saxpy(10., inp1, std::to_array(cstyle), outp.begin());
    sr::copy(outp, cout);
    std::cout << ":::::::::::::::::::::\n";
    saxpy(outp.begin(), 10., inp1, inp3);
    sr::copy(outp, cout);
    std::cout << ":::::::::::::::::::::\n";
}

