#include <cxxopts.hpp>
#include <chrono>
#include <print>
#include <span>
#include <tbb/global_control.h>
#include "Matrix_naive.hh"
//#include "Matrix_xtmp.hh"
//#include "Matrix_blocks.hh"
//#include "Matrix_ni.hh"
//#include "Matrix_recursive_blocks.hh"

namespace sc = std::chrono;

auto main(int argc, char* argv[]) -> int
{
    cxxopts::Options cmd{"matmul", "Experiments with hand-optimized matrix multiplication"};
    cmd.add_options()
	    ("s,size", "Matrix size", cxxopts::value<std::size_t>()->default_value("64"))
	    ("r,reps", "How many times to repeat calculation before reporting",
	         cxxopts::value<std::size_t>()->default_value("1"))
	    ("t,threads", "Number of threads to use in the calculation",
	         cxxopts::value<std::size_t>()->default_value("1"))
	    ("y,verify", "Check answer against a serial straightforward calculation",
	         cxxopts::value<bool>()->default_value("false"))
	    ("h,help", "Print usage.");

    auto args = cmd.parse(argc, argv);
    if (args.count("help")) {
	    std::print("{}\n", cmd.help());
	    return 0;
    }
    auto N = args["size"].as<std::size_t>();
    auto nrep = args["reps"].as<std::size_t>();
    auto nthr = args["threads"].as<std::size_t>();
    auto verify = args["verify"].as<bool>();

    tbb::global_control tbbctl{tbb::global_control::parameter::max_allowed_parallelism, nthr};
    auto t0 = sc::high_resolution_clock::now();
    matrix X(N, N), Y(N, N), Z(N, N);
    X.random_fill();
    Y.random_fill();
    auto t1 = sc::high_resolution_clock::now();
    std::cout << "Time taken to fill the matrices = "
              << sc::duration<double>(t1 - t0).count() << " seconds\n";

    auto res = 0.;
    // Start the stop watch!
    t0 = sc::high_resolution_clock::now();
        // We repeat a computation a few times to get a better time estimate
        for (int rep = 0; rep < nrep; ++rep) {
            // This is the computation we are timing
            Z = X * Y;
            res += Z(0, 0);
        }
    t1 = sc::high_resolution_clock::now();
    auto td = sc::duration<double>(t1 - t0).count();

    std::print("Ignore this : {}\n", res);

    std::print("Z = X * Y: size = {}, average time = {} seconds, {} Gflops\n",
		    N, td / nrep,
                    1.0 * static_cast<double>(N * N * (N + N - 1) * nrep) / td / 1.0e9);

    if (verify) {
        std::print("Verifying with bruteforce calculation ...\n");
        matrix Zb(N, N);
        Zb = 0.;
        for (auto i = 0UL; i < N; ++i) {
            for (auto k = 0UL; k < N; ++k) {
                auto aik = X(i, k);
                for (auto j = 0UL; j < N; ++j) {
                    Zb(i, j) += aik * Y(k, j);
                }
            }
        }
        double toterr = 0.;
        for (auto i = 0UL; i < N; ++i) {
            for (auto j = 0UL; j < N; ++j) {
                toterr += fabs(Zb(i, j) - Z(i, j));
            }
        }
        std::print("Average error = {}\n", toterr / static_cast<double>(N * N));
    }
}
