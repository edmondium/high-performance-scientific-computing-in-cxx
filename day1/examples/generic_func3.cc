#include <iostream>
#include <string>
#include <concepts>

template <class T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
};

auto f(Addable auto i1, Addable auto i2)
{
    return i1 + i2;
}

int main()
{
    using namespace std::string_literals;
    std::cout << f(1, 2) << "\n"; 
    std::cout << f("1"s, "2"s) << "\n"; 
    std::cout << f("1", "2") << "\n"; 
}

