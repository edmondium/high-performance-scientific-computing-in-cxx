#include <algorithm>
#include <execution>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

auto random_number_generator() -> double
{
    // usage of thread local random engines allows running the generator in concurrent mode
    thread_local static std::default_random_engine rd;
    std::uniform_real_distribution<double> dist(0, 1);
    return dist(rd);
}

auto main(int argc, char* argv[]) -> int
{

    const size_t size = 10000000;

    std::vector<double> v1(size), v2(size);

    std::generate(std::execution::par, v1.begin(), v1.end(), random_number_generator);
    std::generate(std::execution::par, v2.begin(), v2.end(), random_number_generator);

    //the dot product calculation
    double res = std::transform_reduce(std::execution::par_unseq, v1.cbegin(), v1.cend(), v2.cbegin(), .0,
        std::plus<double>(), std::multiplies<double>());

    std::cout << "The inner product is: " << res << "\n";
}

