#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/transform.h>
#include <thrust/count.h>
#include <thrust/functional.h>
#include <random>
#include <chrono>

using namespace thrust::placeholders;

int main()
{
    std::random_device seed;
    std::mt19937_64 engine{seed()};
    std::uniform_real_distribution<double> dist;
    auto gen = [&]{ return dist(engine); };
    thrust::host_vector<double> X(1 << 16), Y(1 << 16);
    thrust::generate(X.begin(), X.end(), gen);
    thrust::generate(Y.begin(), Y.end(), gen);
    const double a = 0.37453;
    thrust::device_vector<double> dX = X;
    thrust::device_vector<double> dY = Y;
    thrust::transform(dX.begin(), dX.end(), dY.begin(), dY.begin(),
    //                  (a * _1 + _2));
    [a] __host__ __device__ (double x, double y){ double z = a*x + y; return z; });

    int morethanhalf = thrust::count_if(dY.begin(), dY.end(), [] __device__ (auto y){return y > 0.5;});
    std::cout << "After saxpy operation, device array contains " << morethanhalf
              << " numbers greater than 0.5\n";
}


