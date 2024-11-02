#include <xsimd/xsimd.hpp>
#include <iostream>

using Arch = xsimd::avx2;

auto main() -> int
{
    using btype = xsimd::batch<double, Arch>;
    btype x{1., 2., 3., 4.};
    btype y{4., 3., 2., 1.};
    std::cout << x + y << "\n";
}

