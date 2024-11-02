#include <iostream>
#include <string>
#include <chrono>

__global__ void mul(const double *A, const double *B, double *C, size_t N)
{
    auto i = threadIdx.x + blockIdx.x * blockDim.x;
    auto j = threadIdx.y + blockIdx.y * blockDim.y;
    double res{};
    if (i<N && j<N) 
        for (size_t k=0ul; k<N; ++k) {
            res += A[N*i + k] * B[N*k +j];
    }
    C[N*i + j] = res;
}

int main(int argc, char *argv[])
{
    const unsigned N = (argc > 1) ? std::stoul(argv[1]) : 2048u;
    double *a=nullptr, *b=nullptr, *c=nullptr;
    cudaMallocManaged(&a, N*N*sizeof(double));
    cudaMallocManaged(&b, N*N*sizeof(double));
    cudaMallocManaged(&c, N*N*sizeof(double));
    for (size_t i=0ul; i < N*N; ++i) {
        a[i] = 1.1;
        b[i] = 0.89;
    }
    auto t0 = std::chrono::high_resolution_clock::now();
    dim3 ThreadsPerBlock{16,16};
    dim3 NumBlocks{N/ThreadsPerBlock.x,N/ThreadsPerBlock.y};
    mul<<<NumBlocks, ThreadsPerBlock >>>(a, b, c, N);
    cudaDeviceSynchronize();
    auto t1 = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration<double>(t1-t0).count();
    std::cout << (2.0 * N -1.) * N * N * 1.0e-9 / dt << " GFlops\n";
}

