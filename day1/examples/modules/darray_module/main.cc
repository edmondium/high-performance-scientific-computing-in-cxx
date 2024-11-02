#include <string>
#include <iostream>
import mymodule;

auto main() -> int
{
    darray d1 { 1, 2, 3, 4, 5 }; // CTAD works!
    //darray<int> d1{1, 2, 3, 4, 5};
    darray<std::string> d2 { "a", "b", "c" }; 
    // Explicit type required above, since "a", "b" etc are C-strings, and we want C++ strings
    auto d3 = d1; //Copy
    darray<int> d4 { 10 }; // This and the following line have a subtle difference
    darray<int> d5(10); // This is the only situation where constructor calls with {} and () mean different things.
    darray<std::string> d6 { std::move(d2) }; // d2 should be empty and d6 must have all data after this.
    std::cout << "d1 = " << d1 << "\n";
    std::cout << "d2 = " << d2 << "\n";
    std::cout << "d3 = " << d3 << "\n";
    std::cout << "d4 = " << d4 << "\n";
    std::cout << "d5 = " << d5 << "\n";
    std::cout << "d6 = " << d6 << "\n";
}
