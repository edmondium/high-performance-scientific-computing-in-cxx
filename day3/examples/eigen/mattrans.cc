#include <cxxopts.hpp>
#include <Eigen/Dense>
#include <format>
#include <chrono>
#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    namespace sc = std::chrono;
    cxxopts::Options cmd{ "mattrans", "Matrix transpose using Eigen."};
    // clang-format off
    cmd.add_options()
            ("s,size", "square matrix size", cxxopts::value<std::size_t>()->default_value("3"))
            ("r,reps", "number of times the calculation is repeated for timings",
                 cxxopts::value<std::size_t>()->default_value("1"))
            ("h,help", "Print usage");
    // clang-format on
    auto args = cmd.parse(argc, argv);

    if (args.count("help")) {
        std::cout << std::format("{}\n", cmd.help());
        return 1;
    }

    const auto N = args["size"].as<std::size_t>();
    const auto nrep = args["reps"].as<std::size_t>();

    bool err{ false };
    err |= (N < 1); // Size must be larger than 1
    if (err) {
	    std::cout << std::format("{}\n", cmd.help());
        return 1;
    }

    Eigen::MatrixXd X(N, N), Y(N, N);
    auto t0 = sc::high_resolution_clock::now();
    X = Eigen::MatrixXd::Random(N, N);
    auto t1 = sc::high_resolution_clock::now();
    std::cout << std::format("Time taken to fill the matrices = {} seconds\n",
               sc::duration<double>(t1 - t0).count());
    // Start the stop watch!
    t0 = sc::high_resolution_clock::now();
    // We repeat a computation a few times to get a better time estimate
    for (unsigned rep = 0; rep < nrep; ++rep) {
        // This is the computation we are timing
        Y.noalias() = X.transpose();
        //X.transposeInPlace();
        //Y.noalias() = X.transpose().transpose();
        //Y.noalias() = X;
    }
    t1 = sc::high_resolution_clock::now();
    auto td = sc::duration<double>(t1 - t0).count();

    std::cout << std::format("Y = X.transpose(): size = {:12} average time {} nanoseconds per element\n",
		  N, 1.0e9 * td / (nrep * N * N));
}
