#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>
#include <vector>
#include <array>

namespace sr = std::ranges;
template <std::floating_point D, sr::input_range IR, std::weakly_incrementable OI>
requires std::is_same_v<D, std::iter_value_t<IR>>
         and std::indirectly_writable<OI, D>
auto saxpy(D a, IR x, IR y, OI z) -> void
{
    sr::transform(x, y, z, [a](auto X, auto Y) { return a * X + Y; });
} 

template <std::floating_point D, sr::input_range IR, std::weakly_incrementable OI>
requires std::is_same_v<D, std::iter_value_t<IR>>
         and std::indirectly_writable<OI, D>
auto saxpy(OI z, D a, IR x, IR y) -> void
{
    sr::transform(x, y, z, [a](const auto& X, const auto& Y) { return a * X + Y; });
} 

auto main() -> int
{
    std::vector inp1 { 1., 2., 3., 4., 5. };
    std::vector inp2 { 9., 8., 7., 6., 5. };
    std::array  inp3 { 1., 2., 3., 4., 5. };
    std::array  inp4 { 9., 8., 7., 6., 5. };
    std::ostream_iterator<double> out { std::cout, "\n" };
    saxpy(10., inp1, inp2, out);
    std::cout << ":::::::::::::::::::::\n";
    saxpy(out, 10., inp1, inp2);
    std::cout << ":::::::::::::::::::::\n";
    saxpy(10., inp3, inp4, out);
    std::cout << ":::::::::::::::::::::\n";
    saxpy(out, 10., inp3, inp4);
}

