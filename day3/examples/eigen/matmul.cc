#include <cxxopts.hpp>
#include <Eigen/Dense>
#include <chrono>
#include <print>
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
    namespace sc = std::chrono;
    cxxopts::Options cmd{ "matmul", "Matrix multiplication using Eigen."};
    // clang-format off
    cmd.add_options()
	    ("s,size", "square matrix size", cxxopts::value<std::size_t>()->default_value("3"))
	    ("r,reps", "number of times the calculation is repeated for timings",
	         cxxopts::value<std::size_t>()->default_value("1"))
	    ("h,help", "Print usage");
    // clang-format on
    auto args = cmd.parse(argc, argv);

    if (args.count("help")) {
        std::print("{}\n", cmd.help());
        return 1;
    }

    const auto N = args["size"].as<std::size_t>();
    const auto nrep = args["reps"].as<std::size_t>();

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
    auto t1 = sc::high_resolution_clock::now();

    std::print("Time taken to fill the matrices = {} seconds\n",
                     sc::duration<double>(t1 - t0).count());

    // Start the stop watch!
    t0 = sc::high_resolution_clock::now();
    // We repeat a computation a few times to get a better time estimate
    for (size_t rep = 0; rep < nrep; ++rep) {
        // This is the computation we are timing
        Z.noalias() = X * Y;
        //Z = X * Y;
    }
    t1 = sc::high_resolution_clock::now();
    auto td = sc::duration<double>(t1 - t0).count();

    std::print("Z = X * Y: size = {:12}, average time = {} seconds, {} GFlops\n",
		    N, td / nrep, 1.0 * N * N * (N + N - 1) * nrep / td / 1.0e9);
}
