// examples/while_with_break.cc
#include <iostream>
#include <string>
#include <bit>
#include <bitset>

auto countdown(unsigned long N) -> void
{
    while (N > 0) {
        std::cout << N << "\n";
        if (std::popcount(N) == 3) {
            std::cout << "Reached exceptional termination with N = " << N
                      << ", with binary representation " << std::bitset<8*sizeof(N)>(N) << "\n";
            break;
        }
        N = N -1;
    }
}

auto main(int argc, char *argv[]) -> int
{
    if (argc > 1) {
        countdown(std::stoul(argv[1]));
    }
}

