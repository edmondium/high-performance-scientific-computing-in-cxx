#include "array2d.hh"
#include <iostream>

auto main() -> int
{
    array2d<size_t> A(10, 10);
    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 10; ++j) {
            A(i, j) = i + j;
        }
    }
    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 10; ++j) {
            std::cout << A[i][j] << "  ";
        }
        std::cout << "\n";
    }
}
