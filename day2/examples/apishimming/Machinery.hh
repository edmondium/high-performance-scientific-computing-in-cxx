#include <iostream>

class Machinery {
public:
    auto calculate() -> size_t
    {
        std::cout << "Called the simple but possibly slow function calculate.\n";
        return 42;
    }
// Compile and run once with the following two functions commented out.
// Then, uncomment the two functions below, but do nothing anywhere else
// in the code. Nothing in main(), nothing in algo(). And also nothing
// to the calculate() function above. Just uncomment, recompile and run!

    /*
    void helper()
    {
        std::cout << "Called helper function.\n";
    }
    auto calculateFast() const -> size_t
    {
        std::cout << "Called clever fast function calculateFast.\n";
        return 42;
    }
    */
};

