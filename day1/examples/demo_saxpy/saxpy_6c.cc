#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <vector>

template <class T>
concept Number = std::is_floating_point_v<T> or std::is_integral_v<T>;
template <class T1, class T2>
concept ConvertibleTo = std::is_convertible_v<T1, T2>;

template <class A>
concept ArrayLike = requires(A a) {
    typename std::decay_t<A>::value_type;
    { Number<typename std::decay_t<A>::value_type> };
    { a[0UL] } -> ConvertibleTo<typename std::decay_t<A>::value_type>;
};

auto saxpy(Number auto a, ArrayLike auto&& x, decltype(x)&& y, ArrayLike auto&& z)
{
    std::transform(x.begin(), x.end(), y.begin(), z.begin(),
        [a](auto X, auto Y) { return a * X + Y; });
}

auto main() -> int
{
    {
        const std::array inp1 { 1., 2., 3., 4., 5. };
        const std::array inp2 { 9., 8., 7., 6., 5. };
        std::vector outp(inp1.size(), 0.);
        std::ostream_iterator<typename decltype(outp)::value_type> cout { std::cout, "\n" };
        saxpy(10., inp1, inp2, outp);
        copy(outp.begin(), outp.end(), cout);
        std::cout << ":::::::::::::::::::::\n";
    }
    {
        const std::array inp1 { 1, 2, 3, 4, 5 };
        const std::array inp2 { 9, 8, 7, 6, 5 };
        std::vector outp(inp1.size(), 0);
        std::ostream_iterator<typename decltype(outp)::value_type> cout { std::cout, "\n" };
        saxpy(10, inp1, inp2, outp);
        copy(outp.begin(), outp.end(), cout);
        std::cout << ":::::::::::::::::::::\n";
    }
}
