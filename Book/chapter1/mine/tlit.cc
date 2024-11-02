// examples/tlit.cc
#include <iostream>
#include <chrono>
auto main() -> int
{
    using namespace std::chrono_literals;
    auto dur = 1h + 33min + 47s;
    std::cout << dur.count() << "\n";
}

