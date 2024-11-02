#include <iostream>
#include <string>
#include <iomanip>

template <class T>
auto minval(T x, T y) -> T
{
    if (x <= y) return x;
    return y;
}

auto main() -> int
{
    using namespace std::string_literals;
    std::cout << "Min of " << -12 << " and " << 12 << " is " << minval(-12, 12) << "\n";
    std::cout << "Min of " << -1.2 << " and " << 1.2 << " is " << minval(-1.2, 1.2) << "\n";
    std::cout << "Min of " << std::quoted("-12"s) << " and " << std::quoted("12"s) << " is " << std::quoted(minval("-12"s, "12"s)) << "\n";
    std::cout << "Min of " << "-12"s << " and " << 12 << " is " << minval("-12"s, 12) << "\n";
}

