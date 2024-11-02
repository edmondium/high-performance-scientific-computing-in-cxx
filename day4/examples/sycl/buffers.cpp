#include <sycl.hpp>
#include <iostream>
#include <vector>

auto main() -> int {
    auto N{1'000'000};
    std::vector v(N, 0.0);

    {
    // Create a buffer buf from v


        sycl::buffer<double, 2> buf2{sycl::range{1000, 1000}};
    }
}
