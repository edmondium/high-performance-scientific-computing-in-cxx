#include <iostream>
#include <type_traits>

template <class T>
concept Integral = std::is_integral_v<T>;

constexpr auto gcd(Integral auto a, Integral auto b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
auto main() -> int
{
    // Wont compile, until both the following arguments
    // are changed into integral types.
    std::cout << gcd(149935, 47295.) << "\n";
}
