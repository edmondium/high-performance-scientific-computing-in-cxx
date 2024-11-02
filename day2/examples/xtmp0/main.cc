#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include "naive_vec.hh"
//#include "xtmp_vec0.hh"
//#include "xtmp_vec1.hh"

auto main(int argc, char* argv[]) -> int
{
    int N { 0 }, nrep { 10 };
    double a = 1.0;
    bool err { false };
    if (argc < 3)
        err = true; // We expect at least 2 arguments
    else {
        try {
            N = std::stoi(argv[1]);
            a = std::stod(argv[2]);
        } catch (...) {
            // If the right kind of values can't be inferred from the input, it's an error.
            err = true;
        }
    }
    err |= (N < 1); // Size must be larger than 1
    if (err) {
        std::cerr << "Usage " << argv[0] << " positive_integer floating_point_number\n";
        return 1;
    }
    // Create 4 vectors of doubles. They are of a user defined type, to illustrate a point.
    HPCXX::vec<double> W(N), X(N), Y(N), Z(N);

    std::random_device seed; // non-deterministic random number generator to create a seed
    std::mt19937_64 engine { seed() }; // Mersenne Twister engine
    // We used the non-deterministic generator to initialise of the Mersenne Twister
    std::uniform_real_distribution<> dist;
    auto gen = [&]() mutable { return dist(engine); };
    auto t0 = std::chrono::high_resolution_clock::now();
    std::generate(X.begin(), X.end(), gen);
    std::generate(Y.begin(), Y.end(), gen);
    std::generate(Z.begin(), Z.end(), gen);
    auto t1 = std::chrono::high_resolution_clock::now();
    //std::cout << "Time taken to fill arrays = "
    //          << std::chrono::duration<double>(t1-t0).count() <<" seconds\n";

    // OK. Now, the arrays are full. Start the stop watch!
    t0 = std::chrono::high_resolution_clock::now();
    // We repeat a computation a few times to get a better time estimate
    for (int rep = 0; rep < nrep; ++rep) {
        // This is the computation we are timing
        W = a * X + 2 * a * Y + 3 * a * Z;
    }
    t1 = std::chrono::high_resolution_clock::now();
    auto td = std::chrono::duration<double>(t1 - t0).count();

    std::cout << "a*X+2*a*Y+3*a*Z : size=" << std::setw(12) << N << " a = " << a << " average time "
              << std::scientific << td / nrep << " seconds "
              << N * 5 * nrep / td / 1.0e9 << " Gflops\n";
}
