#include <span>
#include <vector>
#include <iostream>
#include <cxx20ranges>
#include <algorithm>

static std::vector u{2, 3, 4, -1, 9};
static std::vector v{3, 1, 4, 1, 5};
auto get_vec(int c) -> std::span<int> {
    return {(c%2 ==0) ? u : v};
}
auto main(int argc, char* argv[]) -> int {

    //namespace sr = std::ranges;
    auto iter = sr::min_element(get_vec(argc));

    std::cout << "Minimum " << *iter << "\n";
}

