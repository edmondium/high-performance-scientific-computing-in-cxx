#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>
#include <string>
#include <execution>

constexpr auto Lambda = 0.75;
constexpr auto L2 = Lambda * Lambda;
constexpr auto cut = 4.3;
constexpr auto cut2 = cut * cut;
constexpr auto icut2 = 1.0 / cut2;
constexpr auto ksa = 0.1;
constexpr auto sixdivLLcut2 = 6.0 / (Lambda * Lambda * cut2);

template <class T>
constexpr auto sqr(T && x) noexcept { return x * x; }

template <class T> using vector_type = std::vector<T>;

template <class T>
auto Vexv(T r2, T sigsa12) -> T
{
    auto sg2 = static_cast<T>(sqr(Lambda * sigsa12));
    auto a = static_cast<T>(icut2 * sqr(sigsa12));
    a = a * a * a;
    a = a * a;
    auto b = static_cast<T>(sixdivLLcut2 * a);
    a = 7.0 * a; 
    T r6 = sg2 / r2;
    r6 = r6 * r6 * r6;
    return ksa * (r6 * r6 + a + b * r2);
}

auto exvolcalc(const vector_type<double>& R2, const vector_type<double>& S12) -> double
{
    return 
    std::transform_reduce(std::execution::par, R2.begin(), R2.end(), S12.begin(), 
        0., std::plus<double>{}, [](auto r2, auto s12){
        return Vexv(r2, s12);
    });
}

struct options {
    void usage(std::string prog)
    {
        std::cerr << "Usage\n" << prog << " -size NUM [-reps NUM] [-verify]\n";
        exit(1);
    }
    options(int argc, char * argv[]) {
        using namespace std::string_literals;
        if (argc < 2) {
            usage(argv[0]);
        }
        int pos = 0;
        while (++pos < argc) {
            if (argv[pos] == "-size"s) N = std::stoul(argv[++pos]);
            else if (argv[pos] == "-reps"s) nrep = std::stoul(argv[++pos]);
            else if (argv[pos] == "-verify"s) verify = true;
            else {
                std::cerr << "Invalid token " << argv[pos] << " at position " << pos << " on command line.\n";
                usage(argv[0]);
            }
        }
    }
    size_t N = 1000ul;
    size_t nrep = 1;
    bool verify = false;
};

auto main(int argc, char* argv[]) -> int
{
    auto [N, nrep, verify] = options(argc, argv);

    std::random_device seed{};
    //std::mt19937_64 eng{seed()};
    std::mt19937_64 eng{123};
    std::uniform_real_distribution<> dist;
    auto gen = [&]()mutable { return dist(eng); };

    vector_type<double> R2(N, 0.), S12(N, 0.);
    {
        std::cout << "Filling 2 arrays of size " << N << " ...\n";
        auto t0 = std::chrono::high_resolution_clock::now();
        std::generate(R2.begin(), R2.end(), [&]{return 0.5 + 10 * gen(); });
        std::generate(S12.begin(), S12.end(), gen);
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << "Time taken = " << std::chrono::duration<double>(t1-t0).count() << " seconds\n";
    }
    {
        std::cout << "Calculating exvol ... (averaging over "<< nrep << " calculations) \n";
        double tottime = 0., totval =0.;
        for (size_t j = 0; j < nrep; ++j) {
            auto t0 = std::chrono::high_resolution_clock::now();
            double tot = exvolcalc(R2, S12);
            auto t1 = std::chrono::high_resolution_clock::now();
            auto timetaken = std::chrono::duration<double>(t1-t0).count();
            tottime += timetaken;
            totval += tot;
        }
        std::cout << "Calculated value = " << totval/nrep << "\n";
        std::cout << "Time taken = " << tottime/nrep << " seconds\t :: " << nrep * 17.0 * R2.size() / tottime / 1.0e9 << " GFlops\n";
    }
}

