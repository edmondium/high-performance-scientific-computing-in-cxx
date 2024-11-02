#include <iostream>

struct pars { int offset, size; };
auto example_func(pars p)
{
    for (int i = 0; i < p.size; ++i)
        std::cout << p.offset + i << "\n";
    return p.size;
}

auto main() -> int
{
    example_func({.offset = 5, .size = 10});
}


