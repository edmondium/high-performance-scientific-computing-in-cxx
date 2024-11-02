#include <iostream>
#include <cxx20ranges>
#include <span>
#include <vector>
#include <valarray>
#include <list>
#include <array>
#include <string>
// Defined in cxx20ranges...
// namespace sr = std::ranges;
// namespace sv = sr::views;

auto sum(sr::input_range auto&& seq)
{
    std::iter_value_t<decltype(seq)> ans{};
    for (auto x : seq) ans += x;
    return ans;
}

int main()
{
    using namespace std::string_literals;
    std::cout << "vector : " << sum(std::vector({ 9,8,7,2 } )) << "\n";
    std::cout << "list : " << sum(std::list({ 9,8,7,2 } )) << "\n";
    std::cout << "valarray : " << sum(std::valarray({ 9,8,7,2 } )) << "\n";
    std::cout << "array : " << sum(std::array<int,4>({ 9,8,7,2 } )) << "\n";
    std::cout << "array : " << sum(std::array<std::string, 4>({ "9"s,"8"s,"7"s,"2"s } )) << "\n";
    int A[]{1,2,3};
    std::cout << "C-array wrapped by span : " << sum(std::span(A)) << "\n";
}

