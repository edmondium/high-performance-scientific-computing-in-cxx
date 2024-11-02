// examples/overload_w_concepts.cc
#include <print>
#include <concepts>
#include <string>
#include <boost/core/demangle.hpp>

template <class N> concept Number = std::floating_point<N> || std::integral<N>;
template <class N> concept NotNumber = not Number<N>; 

namespace B = boost::core;
void proc(Number auto&& x)
{
    std::print("Called proc for numbers with argument value {} of type {}\n", x, B::demangle(typeid(x).name()));
}
void proc(NotNumber auto&& x) 
{
    std::print("Called proc for non-numbers with argument value {} of type {}\n", x, B::demangle(typeid(x).name()));
}

auto main() -> int
{
    using namespace std::literals;
    proc(-1);
    proc(88UL);
    proc("0118 999 88191 9119725 3");
    proc(3.141);
    proc("eighty"s);
}

