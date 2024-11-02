// examples/quadratic0.cc

#include <iostream>
#include <cmath>

auto solve_quadratic(double a, double b, double c) -> std::pair<double, double>
{
    auto D = b * b - 4 * a * c;
    auto q = -0.5 * ( b + std::copysign(std::sqrt(D), b) );
    return { q / a, c / q };
}

auto main(int argc, char *argv[]) -> int
{
    auto c1 = std::stod(argv[1]);
    auto c2 = std::stod(argv[2]);
    auto c3 = std::stod(argv[3]);
    auto [root1, root2] = solve_quadratic(c1, c2, c3);
    std::cout << "Quadratic equation " 
              << c1 << " x^2 + " << c2 << " x + " << c3 
              << " = 0 \nhas solutions\n"
              << "x1 = " << root1 << "\n"
              << "x2 = " << root2 << "\n";
}

