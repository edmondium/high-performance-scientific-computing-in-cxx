#include <iostream>
#include <list>

template <typename V>
void f(const V& v, const typename V::iterator* jt = nullptr)
{
    std::cout << "Using container type overload\n";
    for (auto x : v)
        std::cout << x << " ";
    std::cout << "\n";
}

void f(...)
{
    std::cout << "Using catch all overload\n";
}

auto main() -> int
{
    std::list L { 0.1, 0.2, 0.3, 0.4, 0.5, 0.6 };
    int A[4] { 4, 3, 2, 1 };
    f(A);
    f(L);
}
