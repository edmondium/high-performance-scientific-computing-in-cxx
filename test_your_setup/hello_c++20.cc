#include <iostream>
#include <type_traits>

auto message(auto&& x)
{
    std::cout << x << "\n";
}

template <class T>
concept is_a_number = std::is_integral_v<T> or std::is_floating_point_v<T>;

auto main() -> int
{
    message("Hello, world!");
    auto n = 1234.0;
    if constexpr (is_a_number<decltype(n)>)
	std::cout << n << " is a number.\n";
    else
	std::cout << n << " is not a number!\n";
}

