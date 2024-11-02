#include <algorithm>
#include <iostream>
#include <type_traits>

struct property1 {
};
struct property2 {
};

template <class T, class U>
void do_something(T&& t, U&& u, property1, property1)
{
    std::cout << "Function for two objects with property1\n";
    std::cout << "Arguments : " << t.name() << " and " << u.name() << "\n";
}
template <class T, class U>
void do_something(T&& t, U&& u, property1, property2)
{
    std::cout << "Function for arguments with property1 and property2\n";
    auto nm = u.name();
    std::reverse(nm.begin(), nm.end());
    std::cout << "Arguments : " << t.name() << " and " << nm << "\n";
}
template <class T, class U>
void do_something(T&& t, U&& u, property2, property1)
{
    std::cout << "Function for arguments with property2 and property1\n";
    auto nm = t.name();
    std::reverse(nm.begin(), nm.end());
    std::cout << "Arguments : " << nm << " and " << u.name() << "\n";
}
template <class T, class U>
void do_something(T&& t, U&& u, property2, property2)
{
    std::cout << "Function for two objects with property2\n";
    auto nm = t.name();
    std::reverse(nm.begin(), nm.end());
    auto mn = u.name();
    std::reverse(mn.begin(), mn.end());
    std::cout << "Arguments : " << nm << " and " << mn << "\n";
}

template <class T, class U>
void do_something(T t, U u)
{
    do_something(t, u, typename T::tag {}, typename U::tag {});
}

class Base {
public:
    Base(std::string s)
        : nm { s }
    {
    }
    inline auto name() const -> std::string { return nm; }

private:
    std::string nm;
};

struct D1 : public Base {
    using tag = property1;
    using Base::Base;
};
struct D2 : public Base {
    using tag = property2;
    using Base::Base;
};

struct Unrelated {
    using tag = property1;
    size_t val;
    auto name() const { return std::to_string(val); }
};

auto main() -> int
{
    D1 d1 { "One" };
    D2 d2 { "Two" };
    D1 d3 { "Three" };
    D2 d4 { "Four" };
    do_something(d1, d2);
    do_something(d1, d3);
    do_something(d4, d1);
    do_something(d2, d4);
    Unrelated uu { 12345 };
    do_something(d4, uu);
}
