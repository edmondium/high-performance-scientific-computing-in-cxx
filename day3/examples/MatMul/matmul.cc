#include <chrono>
#include <iomanip>
#include <iostream>
#include <span>
#include <tbb/task_arena.h>
#include "Matrix_naive.hh"
// #include "Matrix_xtmp.hh"
// #include "Matrix_blocks.hh"
// #include "Matrix_ni.hh"
// #include "Matrix_recursive_blocks.hh"

struct options {
    void usage(std::string_view prog)
    {
        std::cerr << "Usage\n"
                  << prog << " -size NUM [-reps NUM] [-threads NUM] [-verify]\n";
        exit(1);
    }
    options(int argc, char* argv[])
    {
        using namespace std::string_literals;
        std::span args(argv, argc);
        if (argc < 2) {
            usage(args[0]);
        }
        int pos = 0;
        while (++pos < argc) {
            if (args[pos] == "-size"s)
                N = std::stoul(args[++pos]);
            else if (args[pos] == "-reps"s)
                nrep = std::stoi(args[++pos]);
            else if (args[pos] == "-threads"s)
                nthr = std::stoi(args[++pos]);
            else if (args[pos] == "-verify"s)
                verify = true;
            else if (args[pos] == "-help"s)
                usage(args[0]);
            else {
                std::cerr << "Invalid token " << args[pos]
                          << " at position " << pos << " on command line.\n";
                usage(args[0]);
            }
        }
    }
    size_t N = 64UL;
    int nrep = 1, nthr = 1;
    bool verify = false;
};

auto main(int argc, char* argv[]) -> int
{
    auto&& [N, nrep, nthr, verify] = options(argc, argv);
    tbb::task_arena main_executor;
    main_executor.initialize(nthr);
    auto t0 = std::chrono::high_resolution_clock::now();
    matrix X(N, N), Y(N, N), Z(N, N);
    main_executor.execute([&] {
        X.random_fill();
        Y.random_fill();
    });
    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << "Time taken to fill the matrices = "
              << std::chrono::duration<double>(t1 - t0).count() << " seconds\n";

    auto res = 0.;
    // Start the stop watch!
    t0 = std::chrono::high_resolution_clock::now();
    main_executor.execute([&, nrep = nrep] {
        // We repeat a computation a few times to get a better time estimate
        for (int rep = 0; rep < nrep; ++rep) {
            // This is the computation we are timing
            Z = X * Y;
            res += Z(0, 0);
        }
    });
    t1 = std::chrono::high_resolution_clock::now();
    auto td = std::chrono::duration<double>(t1 - t0).count();

    std::cout << "Ignore this : " << res << "\n";

    std::cout << "Z=X*Y: size=" << std::setw(12) << N << " average time = "
              << td / nrep << " seconds "
              << 1.0 * static_cast<double>(N * N * (N + N - 1) * nrep) / td / 1.0e9
              << " Gflops\n";

    if (verify) {
        std::cout << "Verifying with bruteforce calculation ...\n";
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
        std::cerr << "Average error = " << toterr / static_cast<double>(N * N)
                  << "\n";
    }
    std::cout.flush();
}
