#include <iostream>

struct v3 { double x, y, z; };
struct pars { int offset; v3 velocity; };
std::ostream & operator<<(std::ostream & os, const v3 & v) { return os << v.x << ", " << v.y << ", " << v.z << " "; }
auto example_func(pars p)
{
    std::cout << p.offset << " with velocity " << p.velocity << "\n";
}

int main()
{
    example_func({.offset = 5, .velocity = {.x=1., .y = 2., .z=3.}});
}


