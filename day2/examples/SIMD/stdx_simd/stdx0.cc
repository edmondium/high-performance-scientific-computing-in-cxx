#include <experimental/simd>
#include <iostream>

namespace stdx = std::experimental;
void println(std::string_view name, const auto& a)
{
    std::cout << name << ": ";
    for (std::size_t i{}; i != std::size(a); ++i)
        std::cout << a[i] << ' ';
    std::cout << '\n';
}

auto main() -> int
{
    using T = double;
    using btype = stdx::native_simd<T>;
    btype x([](int i){ return static_cast<T>(i); });
    btype y([](int i){ return static_cast<T>(btype::size() - i); });
    println("x + y = ", x + y);
}

