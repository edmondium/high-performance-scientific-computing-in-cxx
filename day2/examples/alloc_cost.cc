#include "timeit.hh"
#include <print>
#include <random>
#include <vector>

constexpr auto ndim = 5UL;

auto random_vector(size_t n)
{
    std::vector<double> ans(n);
    static thread_local auto gen = [engine = std::mt19937_64 { std::random_device {}() },
                                       dist = std::uniform_real_distribution<> {}]() mutable {
        return dist(engine);
    };
    for (auto& el : ans)
        el = gen();
    return ans;
}
template <size_t n>
auto random_array()
{
    std::array<double, n> ans {};
    static thread_local auto gen = [engine = std::mt19937_64 { std::random_device {}() },
                                       dist = std::uniform_real_distribution<> {}]() mutable {
        return dist(engine);
    };
    for (auto& el : ans)
        el = gen();
    return ans;
}

auto main() -> int
{
    constexpr auto nsamples = 10000UL;
    timeit("Receiving newly created std::vector from function", 10UL,
        [] {
            auto tot = random_vector(ndim);
            for (auto i = 1UL; i < nsamples; ++i) {
                auto v3 = random_vector(ndim);
                for (auto j = 0UL; j < ndim; ++j)
                    tot[j] += v3[j];
            }
            for (auto j = 0UL; j < ndim; ++j)
                tot[j] /= nsamples;
            std::print("avg. = ({}, {}, {})\n", tot[0], tot[1], tot[2]);
        });
    timeit("Receiving newly created std::array from function", 10UL,
        [] {
            auto tot = random_array<ndim>();
            for (auto i = 1UL; i < nsamples; ++i) {
                auto v3 = random_array<ndim>();
                for (auto j = 0UL; j < ndim; ++j)
                    tot[j] += v3[j];
            }
            for (auto j = 0UL; j < ndim; ++j)
                tot[j] /= nsamples;
            std::print("avg. = ({}, {}, {})\n", tot[0], tot[1], tot[2]);
        });
}
