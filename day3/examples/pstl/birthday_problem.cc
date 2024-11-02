#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cxx20ranges>
#include <execution>
#include <limits>
#include <atomic>
#include "CountingIterator.hh"
#include <numeric>
//#include <tbb/scalable_allocator.h>

/*
 * Run it first as it is. Then, try replacing the vector type with the
 * scalable allocator type from the Threading Building Blocks (TBB).
 * Then do the modification suggested in the function 
 * probability_for_equal_birthdays(). Run the program in each variant
 * and check how long it takes by using the time command:
 *
 * time executablename [OPTIONS]
 *
 */
// defined in cxx20ranges
// namespace sr = std::ranges;
// namespace sv = std::views;

template <class T>
//using VectorType = std::vector<T, tbb::scalable_allocator<T>>;
using VectorType = std::vector<T>;

auto sample_group(size_t n) -> VectorType<int>
{
    VectorType<int> grp(n, 0);
    static thread_local std::mt19937_64 eng{ std::random_device{}() };
    static thread_local std::uniform_int_distribution<> dist{ 0, 365 };
    auto birthdays = [&]{ return dist(eng); };
    std::generate(grp.begin(), grp.end(), birthdays);
    return grp;
}

auto probability_for_equal_birthdays(size_t group_size, size_t nexpt = 10'000'000UL) -> double
{
    // transform_reduce(start, end, init, accumulator_op, transform_op);
    // That's the normal syntax of transform_reduce. But, there is another
    // overload that takes one extra argument at the front: an execution policy.
    // Add one extra argument to transform_reduce: std::execution::par which
    // specifies a parallel execution policy, and see what happens!
    auto nclashes = std::transform_reduce(algo_counter(0UL), algo_counter(nexpt), 0UL, 
            std::plus<size_t>{},
            [&]([[maybe_unused]] auto counter) {
        auto group = sample_group(group_size);
        sr::sort(group);
        auto newend = std::unique(group.begin(), group.end());
        //group.erase(newend, group.end());
        //if (group.size() != group_size) ++nclashes;
        if (newend != group.end()) return 1UL;
        return 0UL;
    });
    return static_cast<double>(nclashes) / nexpt;
}

auto main(int argc, char* argv[]) -> int
{
    auto target_group_size = (argc == 1 ? 50UL : std::stoul(argv[1]));
    std::cout << "Group size\tShared birthday probability\n\n";
    for (auto gs = 0UL; gs < target_group_size; ++gs) {
        std::cout << gs << "\t\t" << probability_for_equal_birthdays(gs) << "\n";
    }
}

