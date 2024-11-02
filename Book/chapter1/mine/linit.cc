// examples/linit.cc
#include <list>
#include <iostream>

auto main() -> int
{
    std::list L(7UL, 0);
    for (auto el : L) std::cout << el << "\n";
}

