#include <algorithm>
#include <chrono>
#include <print>
#include <ranges>
#include <random>
#include <vector>

auto main(int argc, char* argv[]) -> int
{
    namespace sc = std::chrono;
    namespace sr = std::ranges;
    namespace sv = sr::views;
    // Generate data
    std::vector<double> a(10'000'000UL);
    auto b = a;
    auto c = a;

    std::mt19937_64 engine(std::random_device {}());
    std::uniform_real_distribution<> dist {};
    auto gen = [&] { return dist(engine); };
    sr::generate(a, gen);
    sr::generate(b, gen);
    sr::generate(c, gen);

    auto start = sc::high_resolution_clock::now();
    auto sum1 = 0., sum2 = 0.;
    auto totiter = 100U;
    double thres = (argc > 1 ? std::stod(argv[1]) : 0.5);
    for (auto i = 0U; i < totiter; ++i) {
        if (i % 5U == 0U)
            std::print("Wait... (remaining iterations = {})\n", totiter - i );
        // Primary loop
        for (auto j = 0U; j < a.size(); ++j) {
    // The following branch depends on c[j], which has
    // random values. The compiler can not do much about
    // predicting which branch to take. But, if we set
    // thres to 1.0, the processor will find that for
    // every position, c[j] just happens to be smaller.
    // It will then take the first branch every time,
    // facilitating prediction by the CPU. Similarly
    // for thres = 0., we have good hardware branch
    // prediction. To set thres, just pass the value
    // as a command line argument.
            if (c[j] < thres)
                sum1 += (a[j] + b[j]);
            else
                sum2 += (a[j] - b[j]);
        }
    }

    auto t_end = sc::high_resolution_clock::now();
    double elapsedTime = sc::duration<double>(t_end - start).count();

    std::print("Elapsed time = {} seconds.\n", elapsedTime);
    std::print("sum1 = {}, sum2 = {}\n", sum1, sum2);
}
