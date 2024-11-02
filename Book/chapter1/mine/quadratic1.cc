// examples/quadratic1.cc

#include <iostream>
#include <cmath>
#include <optional>

auto solve_quadratic(double a, double b, double c) 
    -> std::optional<std::pair<double, double>>
{
    using namespace std;
    optional<pair<double, double>> solution;
    auto D = b * b - 4 * a * c;
    if (D >= 0) {
        auto q = -0.5 * ( b + std::copysign(std::sqrt(D), b) );
        solution = make_pair(q / a, c / q );
    }
    return solution;
}

auto main(int argc, char *argv[]) -> int
{
    if (argc < 4) {
        std::cerr << "Needs three real numbers as arguments!\n";
        return 1;
    }
    auto c1 = std::stod(argv[1]);
    auto c2 = std::stod(argv[2]);
    auto c3 = std::stod(argv[3]);
    std::cout << "Quadratic equation " << c1 << " x^2 + " << c2 << " x + " << c3 << " = 0 \n";
    auto result = solve_quadratic(c1, c2, c3);
    // result is an optional pair of doubles
    if (result) {
        // result evaluated as a condition gives true, which means the optional
        // contains a value.
        auto [root1, root2] = *result; 
        // *result unpacks the inner value of the optional
        std::cout << "has solutions\n"
              << "x1 = " << root1 << "\n"
              << "x2 = " << root2 << "\n";
    } else {
        // This block of code is executed if the condition of the if statement
        // evaluates to false. In this case, this means the optional
        // does not contain a value.
        std::cout << "No solution is possible in the space of real numbers.\n";
    }
}

