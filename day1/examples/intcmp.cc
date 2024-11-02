#include <print>
#include <utility>

auto main() -> int
{
    std::print("( -1 < 1U ) = {}\n", ( -1 < 1U ));
    std::print("std::cmp_less( -1 , 1U ) = {}\n", std::cmp_less( -1 , 1U ));
}

