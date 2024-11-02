#include <cstdlib>
#include <thrust/copy.h>
#include <thrust/generate.h>
#include <thrust/universal_vector.h>
#include <thrust/sort.h>

auto main() -> int
{
    thrust::universal_vector<int> h_vec(1 << 22);
    std::cout << "Filling host vector with random numbers\n";
    thrust::generate(thrust::host, h_vec.begin(), h_vec.end(), rand);
    std::cout << "Done.\n";

    std::cout << "Sorting vector on device\n";
    thrust::sort(thrust::device, h_vec.begin(), h_vec.end());
    std::cout << "Done.\n";
    std::cout << h_vec[1121] << "\n";
}
