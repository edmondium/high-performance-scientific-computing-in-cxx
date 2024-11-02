#include "timeit.hh"
#include <algorithm>
#include <execution>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

struct Point {
    double x {}, y {};
    auto operator+(Point oth) const noexcept -> Point { return { x + oth.x, y + oth.y }; }
    auto operator-(Point oth) const noexcept -> Point { return { x - oth.x, y - oth.y }; }
    auto norm() const noexcept -> double { return x * x + y * y; }
};
auto operator*(double scl, Point pt) noexcept -> Point { return { scl * pt.x, scl * pt.y }; }
auto gen()
{
    static thread_local std::random_device seed;
    static thread_local std::mt19937_64 engine { seed() };
    static thread_local std::normal_distribution<double> dist { 3.4, 1.2 };
    return Point { dist(engine), dist(engine) };
}

auto main() -> int
{
    std::vector<Point> P(8000000UL);
    std::generate(std::execution::par, P.begin(), P.end(), gen);
    double nrm = 1.0 / P.size();
    auto cms = std::reduce(
        // std::execution::seq,
        // std::execution::par,
        // std::execution::par_unseq,
        P.begin(), P.end(), Point {});
    cms = nrm * cms;
    timeit("transform_reduce", 10UL, [&] {
        double result = std::transform_reduce(
            std::execution::seq,
            // std::execution::par,
            // std::execution::par_unseq,
            P.begin(), P.end(), 0.0, std::plus<double> {},
            [=](Point a) { return nrm * (a - cms).norm(); });
        std::cout << result << '\n';
    });
}
