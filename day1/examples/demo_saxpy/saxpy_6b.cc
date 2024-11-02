#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <vector>
#include <span>

template <class T>
concept Number = std::is_floating_point_v<T> or std::is_integral_v<T>;

template <Number T>
auto saxpy(T a, std::span<const T> x, std::span<const T> y, std::span<T> z)
{
    std::transform(x.begin(), x.end(), y.begin(), z.begin(),
        [a](T X, T Y) { return a * X + Y; });
}

auto main() -> int
{
    {
        const std::array inp1 { 1., 2., 3., 4., 5. };
        const std::array inp2 { 9., 8., 7., 6., 5. };
        std::vector outp(inp1.size(), 0.);
        std::ostream_iterator<double> cout { std::cout, "\n" };
        saxpy(10., {inp1}, {inp2}, {outp});
        copy(outp.begin(), outp.end(), cout);
        std::cout << ":::::::::::::::::::::\n";
    }
    {
        const std::array inp1 { 1, 2, 3, 4, 5 };
        const std::array inp2 { 9, 8, 7, 6, 5 };
        std::vector outp(inp1.size(), 0);
        std::ostream_iterator<int> cout { std::cout, "\n" };
        saxpy(10, {inp1}, {inp2}, {outp});
        copy(outp.begin(), outp.end(), cout);
        std::cout << ":::::::::::::::::::::\n";
    }
}
