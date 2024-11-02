// examples/sort_various.cc
#include <iostream>
#include <string>
#include <ranges>
#include <algorithm>
#include <vector>

auto main() -> int
{
    std::vector<std::string> L{ "Magpies", "are", "birds", "of", "the", "Corvidae", "family" };
    namespace sr = std::ranges;
    namespace sv = std::views;
    std::cout << "Top 3 after alphabetical sorting...\n";
    sr::sort(L);
    for (auto el : L | sv::take(3)) std::cout << el << "\n";
    std::cout << "Top 3 after alphabetical sorting in reverse order ...\n";
    // No sorting required, because we already did that, 
    // and we can just look at it in the reverse order
    for (auto el : L | sv::reverse | sv::take(3)) std::cout << el << "\n";
    std::cout << "Top 3 after sorting by string length ...\n";
    sr::sort(L, [](auto a, auto b) { return a.size() < b.size();} );
    for (auto el : L | sv::take(3)) std::cout << el << "\n";
}

