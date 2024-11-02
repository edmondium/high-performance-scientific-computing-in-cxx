#include <Eigen/Dense>
#include <iomanip>
#include <chrono>
#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    int N{ 0 }, nrep{ 10 };
    bool err{ false };
    if (argc < 2)
        err = true;
    else {
        try {
            N = std::stoi(argv[1]);
        } catch (...) {
            err = true;
        }
    }
    err |= (N < 1); // Size must be larger than 1
    if (err) {
        std::cerr << "Usage " << argv[0] << " positive_integer\n";
        return 1;
    }

    Eigen::MatrixXd X(N, N), Y(N, N);
    auto t0 = std::chrono::high_resolution_clock::now();
    X = Eigen::MatrixXd::Random(N, N);
    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to fill the matrices = "
              << std::chrono::duration<double>(t1 - t0).count() << " seconds\n";
    // Start the stop watch!
    t0 = std::chrono::high_resolution_clock::now();
    // We repeat a computation a few times to get a better time estimate
    for (int rep = 0; rep < nrep; ++rep) {
        // This is the computation we are timing
        Y.noalias() = X.transpose();
        //X.transposeInPlace();
        //Y.noalias() = X.transpose().transpose();
        //Y.noalias() = X;
    }
    t1 = std::chrono::high_resolution_clock::now();
    auto td = std::chrono::duration<double>(t1 - t0).count();

    std::cout << "Y=X.transpose(): size=" << std::setw(12) << N << " average time "
              << std::scientific << 1.0e9 * td / (nrep * N * N) << " nanoseconds per element\n";
}
