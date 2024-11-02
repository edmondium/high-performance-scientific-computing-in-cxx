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
    thrust::device_vector<double> dX = X;
    //auto norm = thrust::transform_reduce(dX.begin(), dX.end(), (_1 * _1), 0., (_1 + _2));
    auto norm = thrust::transform_reduce(dX.begin(), dX.end(), 
                                         [] __device__ (auto a){return a*a;}, 
                                         0., 
                                         [] __device__ (auto a, auto b){return a+b;});

    std::cout << "Transform reduce: norm = " << norm << "\n";
}


