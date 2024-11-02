#include <iostream>
#include <string>
#include <algorithm>
#include <ranges>
#include <complex>
#include <vector>

auto main(int argc, char *argv[]) -> int
{
    namespace sr = std::ranges;
    using namespace std::complex_literals;
    std::vector nums{ 1.+2.i, 0.11+3.229i, 3.1+0.5i, 2.001+1.5i };

    sr::sort(nums, _________ );

    std::cout << "Sorted list of complex numbers, using the given "
              << "comparison operation...\n";
    for (auto num : nums) std::cout << num << "\n";
}

