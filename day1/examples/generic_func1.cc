#include <iostream>
#include <string>

auto f(auto i1, auto i2)
{
    return i1 + i2;
}

// Same as above, but enforce that the parameters have the same type
template <class T>
auto g(T i1, T i2)
{
    return i1 + i2;
}

int main()
{
    using namespace std::string_literals;
    std::cout << f(1, 2) << "\n";
    std::cout << f(1.2, 2.2) << "\n";
    std::cout << f("1"s, "2"s) << "\n";
    //std::cout << f("1"s, 2) << "\n"; // Does not work
    std::cout << g("1"s, 2) << "\n"; // Does not work, but better errors
}

