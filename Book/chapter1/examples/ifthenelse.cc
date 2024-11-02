#include <iostream>
#include <numeric>

auto main(int argc, char *argv[]) -> int
{
    if (auto d = argc * argc; std::gcd(d, 12) >= 4) {
        std::cout << d << "\n";
    } else if (auto e = argc * (argc+1); std::lcm(d, 12) >= 50) {
        std::cout << "gcd(12, " << d << ") < 4 " << "\n";
        std::cout << "lcm(12, " << d << ") >= 50 " << "\n";
        std::cout << " e = " << e << "\n";
    } else {
        std::cout << "gcd(12, " << d << ") < 4 " << "\n";
        std::cout << "lcm(12, " << d << ") < 50 " << "\n";
        std::cout << " e = " << e << "\n";
    }

}

