// examples/iota.cc
#include <iostream>
#include <algorithm>
#include <ranges>

int main()
{
    for (auto i : std::views::iota(4, 10)) std::cout << i << "\n";
}

