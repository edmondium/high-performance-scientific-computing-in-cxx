#include <iostream>
#include <string>
#include <ranges>
#include <algorithm>

auto main(int argc, char *argv[]) -> int
{
    std::vector v { 9., 2., 3., 8., 2., 1., 0., 5., 7., 6., 1., 2. };
    std::cout << "Original sequence of numbers...\n";
    for (auto el : v) std::cout << el << ", ";
    std::cout << "\n";

    decltype(v) w{}; 
    // Create w with the type of v, but initialize as an empty container.
    namespace sr = std::ranges;

    sr::transform(v, std::back_inserter(w), [](auto x) { return x * x; });
    std::cout << "New sequence created form mapping x => x * x ...\n";
    for (auto el : w) std::cout << el << ", ";
    std::cout << "\n";
    

    decltype(v) x;
    sr::copy_if(v, std::back_inserter(x), [](auto x) { return x < 3.0; });
    std::cout << "New sequence created by filtering only the elements satisfying x => (x < 3.0)...\n";
    for (auto el : x) std::cout << el << ", ";
    std::cout << "\n";
    

}

