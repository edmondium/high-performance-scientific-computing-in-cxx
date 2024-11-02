// examples/switchdemo.cc
#include <iostream>

auto main(int argc, char *argv[]) -> int
{
    if (argc > 1) {
        auto choice = std::stoi(argv[1]);  
        switch (choice) {
            case 3: {
                std::cout << "You chose option 3\n";
                break;
            }
            case 2: {
                std::cout << "You chose option 2\n";
                break;
            }
            case 1: {
                std::cout << "You chose option 1\n";
                break;
            }
            case 0: 
            default: {
                std::cout << "You have to choose an option between 1-3\n";
            }
        };
    }
}

