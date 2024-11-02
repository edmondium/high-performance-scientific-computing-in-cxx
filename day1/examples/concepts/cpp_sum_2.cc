#include <iostream>
#include <vector>
#include <list>
#include <ranges>
namespace sr = std::ranges;

template <class T>
using cleanup = std::remove_cvref_t<T>;
template <class T>
using element = std::iter_value_t<cleanup<T>>;
template <class T>
requires sr::forward_range<T>
auto cpp_sum(T&& a, element<T>&& start)
{
    auto res = start;
    for (auto&& el : a) res += el;
    return res;
}

template <class ... T, class U>
requires ((std::same_as<T, U>) && ...)
auto cpp_sum(U&& start, T&& ... a)
{
    return (start + ... + a);
}

auto main() -> int
{
    std::vector v{ 1, 2, 3, 4, 5 };
    std::list l{9.1, 9.2, 9.3, 9.4, 9.5, 9.6};
    std::cout << cpp_sum(v, 0) << "\n";
    std::cout << cpp_sum(l, 0.) << "\n";
    std::cout << cpp_sum(4.5, 9.) << "\n";
    std::cout << cpp_sum(4.5, 3.4, 5., 9.) << "\n";
}

