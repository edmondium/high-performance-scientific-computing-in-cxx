#include "timeit.hh"
#include <array>
#include <iostream>
#include <thread>

constexpr auto WORKLOAD = 1000000000UL;
constexpr auto PARALLEL = 16UL;

struct wrapped1 {
    int val {};
};
struct alignas(std::hardware_destructive_interference_size) wrapped2 {
    int val {};
};

template <class W>
struct func {
void operator()(volatile W* var)
{
    for (unsigned i = 0; i < WORKLOAD / PARALLEL; ++i) {
        var->val = var->val + 1;
    }
}
};

auto main() -> int
{
    timeit("Different threads accumulating to different variables, but different cache lines",
        5UL,
        [] {
            std::array<wrapped2, PARALLEL> arr {};
            {
                std::array<std::jthread, PARALLEL> threads;
                for (unsigned i = 0U; i < PARALLEL; ++i) {
                    threads[i] = std::jthread(func<wrapped2>{}, &arr[i]);
                }
            }
        });
    timeit("Different threads accumulating to different variables, but in the same cache line",
        5UL,
        [] {
            std::array<wrapped1, PARALLEL> arr {};
            {
                std::array<std::jthread, PARALLEL> threads;
                for (unsigned i = 0U; i < PARALLEL; ++i) {
                    threads[i] = std::jthread(func<wrapped1>{}, &arr[i]);
                }
            }
        });
}
