#include <algorithm>
#include <chrono>
#include <format>
#include <ranges>
#include <iostream>
#include <xtensor-blas/xlinalg.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xrandom.hpp>

auto main(int argc, char* argv[]) -> int
{
    auto size = (argc > 1 ? std::stoul(argv[1]) : 4);
    namespace sv = std::views;
    namespace sr = std::ranges;
    auto examples = sv::iota(0UL, 1000UL)
        | sv::transform([=](auto inp) { // generate a random symmetric matrix
              xt::xarray<double> mat = xt::random::rand<double>({ size, size });
              mat = 0.5 * (mat + xt::transpose(mat));
              return mat;
          })
        | sv::transform([](auto&& mat) { // calculate trace and sum of eigenvalues
              auto eigsum = xt::eval(xt::sum(xt::linalg::eigvals(mat)))[0];
              // In xtensor, objects returned by calculations are almost always
              // n-dimensional arrays. Sometimes n==0, when the value is supposed
              // to be a scalar. But, it is still returned as an n-dim array.
              // We have to remember to take the 0'th element to convert that
              // into a scalar entity.
              auto trace = xt::eval(xt::linalg::trace(mat))[0];
              std::cout << std::format("Sum of eigenvalues = {}, trace = {}, diff = {}\n",
                  eigsum.real(), trace, eigsum.real() - trace);
              return fabs(xt::real(eigsum) - trace);
          });
    if (sr::any_of(examples, [](auto vl) { return vl > 1.0e-5; })) {
        std::cout << "Ranges any of found one example where sum of eigenvalues does not match the trace.\n";
    } else
        std::cout << "All test matrices passed the test.\n";
}
