#include <Eigen/Dense>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <algorithm>

double gen()
{
    static thread_local std::minstd_rand engine;
    static thread_local std::uniform_real_distribution<> dist;
    return dist(engine);
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Usage : \n"
                  << argv[0] << " square_matrix_size [nreps]\n";
        return 1;
    }
    unsigned long N{ std::stoul(argv[1]) }, nrep{ 1 };
    if (argc > 2)
        nrep = std::stoi(argv[2]);

    Eigen::MatrixXd X(N, N), Y(N, N), Z(N, N);

    auto t0 = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for collapse(2)
    for (size_t i=0; i<N; ++i) {
	for (size_t j=0; j<N; ++j) {
	    X(i,j) = gen();
	}
    }
    #pragma omp parallel for collapse(2)
    for (size_t i=0; i<N; ++i) {
	for (size_t j=0; j<N; ++j) {
	    Y(i,j) = gen();
	}
    }
    auto t1 = std::chrono::high_resolution_clock::now();

    std::cout << "Time taken to fill the matrices = "
              << std::chrono::duration<double>(t1 - t0).count() << " seconds\n";

    // Start the stop watch!
    t0 = std::chrono::high_resolution_clock::now();
    // We repeat a computation a few times to get a better time estimate
    for (size_t rep = 0; rep < nrep; ++rep) {
        // This is the computation we are timing
        Z.noalias() = X * Y;
        //Z = X*Y;
    }
    t1 = std::chrono::high_resolution_clock::now();
    auto td = std::chrono::duration<double>(t1 - t0).count();

    std::cout << "Z=X*Y: size=" << std::setw(12) << N << " average time = "
              << std::scientific << td / nrep << " seconds "
              << 1.0 * N * N * (N + N - 1) * nrep / td / 1.0e9 << " Gflops\n";
}
