#include <xtensor/xtensor.hpp>
#include <xtensor/xarray.hpp>
#include <xtensor/xio.hpp>
#include <xtensor/xrandom.hpp>
#include <xtensor-blas/xlinalg.hpp>
#include <iostream>

auto main() -> int
{
    auto R = xt::random::rand<double>({4, 4});
    auto eigs = xt::linalg::eigvals(R);
    std::cout << R << "\n\n";
    std::cout << eigs << "\n";
}

