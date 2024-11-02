#include <chrono>
#include <cublas_v2.h>
#include <curand.h>
#include <thrust/device_vector.h>

using namespace thrust::placeholders;

void GPU_fill_random(double* x, int sz)
{
    curandGenerator_t cudagen;
    curandCreateGenerator(&cudagen, CURAND_RNG_PSEUDO_DEFAULT);
    curandSetPseudoRandomGeneratorSeed(cudagen, (unsigned long long)clock());
    curandGenerateUniformDouble(cudagen, x, sz * sz);
}
void gpu_blas_mmul(const cublasHandle_t& handle, const double* A, const double* B, double* C, const int sz)
{
    int lda = sz, ldb = sz, ldc = sz;
    const double aa = 1;
    const double bb = 0.;
    const double* alpha = &aa;
    const double* beta = &bb;
    cublasDgemm(handle, CUBLAS_OP_N, CUBLAS_OP_N, sz, sz, sz, alpha, A, lda, B, ldb, beta, C, ldc);
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: \n"
                  << argv[0] << " square_matrix_size repeat_count\n";
        return 1;
    }
    int size = std::stoi(argv[1]);
    int nrep = 10;
    if (argc > 2)
        nrep = std::stoi(argv[2]);
    thrust::device_vector<double> d_A(size * size), d_B(size * size), d_C(size * size);
    cublasHandle_t handle;
    cublasCreate(&handle);

    // Fill arrays on the GPU using random number generation on the GPU
    GPU_fill_random(thrust::raw_pointer_cast(&d_A[0]), size);
    GPU_fill_random(thrust::raw_pointer_cast(&d_B[0]), size);
    auto t0 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < nrep; ++i) {
        gpu_blas_mmul(handle, thrust::raw_pointer_cast(&d_A[0]),
            thrust::raw_pointer_cast(&d_B[0]),
            thrust::raw_pointer_cast(&d_C[0]),
            size);
        cudaThreadSynchronize();
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    auto tdiff = std::chrono::duration<double>(t1 - t0).count();
    std::cout << "Timing for " << nrep << " matrix multiplications on the GPU (measured on the CPU) = "
              << tdiff << "\n";
    std::cout << "Approximately " << (static_cast<size_t>(size) * size * (size + size - 1) * nrep) / (tdiff * 1.0e9) << " GFlops\n";
    cublasDestroy(handle);
}
