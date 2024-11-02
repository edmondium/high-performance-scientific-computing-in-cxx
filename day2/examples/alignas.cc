#include <iostream>

auto main() -> int
{
    alignas(16) short A[4];
    std::cout << (size_t)(&A) <<"\n";
}

