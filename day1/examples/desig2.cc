#include <iostream>

struct v3 { double x, y, z; };
struct pars { int offset; v3 velocity; };
auto operator<<(std::ostream & os, const v3 & v) -> std::ostream&
{ 
    return os << v.x << ", " << v.y << ", " << v.z << " ";
}
void example_func(pars p)
{
    std::cout << p.offset << " with velocity " << p.velocity << "\n";
}

auto main() -> int
{
    example_func({.offset = 5, .velocity = {.x=1., .y = 2., .z=3.}});
}


