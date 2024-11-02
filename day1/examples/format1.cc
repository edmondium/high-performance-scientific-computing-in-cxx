#include <cmath>
#include <format>
#include <iostream>
#include <string>
#include <tuple>

auto main() -> int
{
    using namespace std;
    using namespace std::string_literals;

    for (auto i = 0UL; i < 110UL; ++i) {
        cout << format(
            "i = {0:010d}, E_tot = {2:16.12f}, E_hb = {1:8.4f}\n",
            i, exp(cos(1.0 * i)), exp(sin(1.0 * i)));
    }
}
