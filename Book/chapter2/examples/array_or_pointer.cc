// examples/array_or_pointer.cc
#include <iostream>

auto f(double arr[4]) -> void
{
    std::cout << "size of function argument in bytes = " << sizeof(decltype(arr)) << "\n";
    std::cout << *arr << "\n";
}

auto main() -> int
{
    double v[4]{1, 2, 3, 4};
    std::cout << "Elements of raw array...\n";
    for (auto a : v) std::cout << a << "\n";
  
    std::cout << "size of raw array in bytes = " << sizeof(decltype(v)) << "\n";
    f(v);
}

