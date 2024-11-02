// examples/ns2.cc
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
auto greet() -> void
{
    std::cout << "You reap what you sow.\n";
}
}
auto main(int argc, char *argv[]) -> int
{
    if (argc > 1) {
        using namespace cxx_course;
        greet();
        std::cout << "The number of participants is "
                  << participant_count << "\n";
    } else {
        using namespace gardening_course;
        greet();
    }
}
