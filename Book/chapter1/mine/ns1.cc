// examples/ns1.cc
#include <iostream>

namespace cxx_course {
unsigned int participant_count { 0 };
auto greet() -> void
{
    std::cout << "Study and practice. Years of it!\n";
}
}
namespace gardening_course {
unsigned int participant_count { 0 };
auto greet() -> void { std::cout << "You reap what you sow.\n"; }
}

auto main() -> int
{
    cxx_course::greet();
}
