#include <cstdlib>
#include <thrust/copy.h>
#include <thrust/device_vector.h>
#include <thrust/generate.h>
#include <thrust/host_vector.h>
#include <thrust/sort.h>

auto main() -> int
{
    // generate 32 M random numbers on the host
    thrust::host_vector<int> h_vec(1 << 16);
    std::cout << "Filling host vector of size " << h_vec.size()
              << " with random numbers\n";
    thrust::generate(h_vec.begin(), h_vec.end(), rand);
    std::cout << "Done.\n";

    // transfer data to the device
    std::cout << "Transfering data to device\n";
    thrust::device_vector<int> d_vec = h_vec;
    std::cout << "Done.\n";

    // sort data on the device (846M keys per second on GeForce GTX 480)
    std::cout << "Reducing vector on device\n";
    int x = thrust::reduce(d_vec.begin(), d_vec.end(), 0, thrust::plus<int>());
    std::cout << "Done. Result = " << x << "\n";
}
