#include <array>
#include <iostream>

auto main() -> int
{
    std::array A{ 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.7, 0.9 };
    std::cout << "Size of array on stack = " << sizeof(A) << "\n";
    std::cout << "size() = " << A.size() << "\n";
}
