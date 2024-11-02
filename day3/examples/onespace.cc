// examples/onespace.cc
#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    std::string line;
    while (getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }
        bool sp{true};
        for (auto c : line) {
            if (isspace(c)) {
                if (not sp) std::cout << '\t';
                sp = true;
            } else {
                sp = false;
                std::cout << c;
            }
        }
        std::cout << "\n";
    }
}

