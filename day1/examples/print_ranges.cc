#include "range_output.hh"
#include <iostream>
#include <iomanip>
#include <list>
#include <string>
#include <vector>
#include <array>

int main()
{
    using namespace std::string_literals;
    using namespace output;
    std::vector v { 1, 2, 3, 4, 5 };
    std::list sl { "one"s, "two"s, "three"s, "four"s, "five"s };
    std::string s { "Test it!" };
    std::cout << "vector<int> output, comma separated  : " << output::comma_separated << v << "\n";
    std::cout << "list<string> output, comma separated : " << output::comma_separated << sl << "\n";
    std::cout << "list<string> output, comma separated2: " << output::comma_separated
              << (sl | std::ranges::views::transform([](auto&& a) { return std::quoted(a); })) << "\n";
    std::cout << "string output, comma separated       : " << output::comma_separated << s << "\n";
    std::cout << "vector<int> output, unseparated      : " << output::unseparated << v << "\n";
    std::cout << "list<string> output, unseparated     : " << output::unseparated << sl << "\n";
    std::cout << "string output, unseparated           : " << output::unseparated << s << "\n";
    std::cout << "vector<int> output, without manipulators   : " << v << "\n";
    std::cout << "list<string> output, without manipulators  : " << sl << "\n";
    std::cout << "string output, without manipulators        : " << s << "\n";
    alignas(64) std::array<double, 4> A {4,3,2,1};
    std::cout << "Displaying std::array : " << A << "\n";
}
