#include <iostream>
#include <string>

template <class T>
concept Addable = requires(T a, T b) {
    { a + b } ;
};


template <class T> concept NotAddable = not Addable<T>;

auto f(Addable auto i1, Addable auto i2)
{
    std::cout << "(using version of function f with Addable parameters) ... ";
    return i1 + i2;
}

auto f(NotAddable auto i1, NotAddable auto i2)
{
    std::cout << "(using version of function f with NotAddable parameters) ... ";
    return i1;
}

int main()
{
    using namespace std::string_literals;
    std::cout << "f(1, 2) --> " << f(1, 2) << "\n"; 
    std::cout << R"(f("1"s, "2"s) --> )" << f("1"s, "2"s) << "\n"; 
    std::cout << R"(f("1", "2") --> )" << f("1", "2") << "\n"; 
}

