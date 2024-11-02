// examples/ns3.cc
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

namespace hpc_course {
using namespace cxx_course;
unsigned long corehours{0};
}

auto main(int argc, char *argv[]) -> int
{
    if (argc > 1) {
        using namespace cxx_course;
        std::cout << "We are using the hpc_course namespace\n";
        greet();
        std::cout << "The number of participants is "
                  << participant_count << "\n";
    } else {
        using namespace hpc_course;
        std::cout << "We are using the hpc_course namespace\n";
        greet();
    }
}

