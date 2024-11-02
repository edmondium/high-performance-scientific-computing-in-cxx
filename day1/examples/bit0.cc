#include <iostream>
#include <bit>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    unsigned long I = ((argc == 1) ? 1UL : std::stoul(argv[1]));
    auto J = I;
    do {
        std::cout << I << "\n";
        I = std::rotl(I, 1);
    } while (I != J);
}

