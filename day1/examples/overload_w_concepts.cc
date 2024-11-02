// examples/overload_w_concepts.cc
#include <iostream>
#include <type_traits>
#include <string>
#include <boost/type_index.hpp>

template <class N> concept Number = std::is_floating_point_v<N> || std::is_integral_v<N>;
template <class N> concept Float = Number<N> && std::is_floating_point_v<N>;

template <class N> concept NotNumber = not Number<N>; 

using namespace boost::typeindex;
auto proc(Number auto&& x) -> void
{
    std::cout << "Called proc for numbers with " << x << " of typeid " << type_id_runtime(x) << "\n";
}
auto proc(Float auto&& x) -> void
{
    std::cout << "Called proc for floats with " << x << " of typeid " << type_id_runtime(x) << "\n";
}
auto proc(NotNumber auto&& x) -> void
{
    std::cout << "Called proc for non-numbers with " << x << " of typeid " << type_id_runtime(x) << "\n";
}

auto main() -> int
{
    using namespace std::string_literals;
    proc(-1);
    proc(88UL);
    proc("0118 999 88191 9119725 3");
    proc(3.141);
    proc("eighty"s);
}

