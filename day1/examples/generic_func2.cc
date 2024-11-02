#include <iostream>
#include <string>

// Same as above, but enforce that the parameters have the same type
template <class T>
auto f(T i1, T i2)
{
    return i1 + i2;
}

int main()
{
    using namespace std::string_literals;
    std::cout << f("1", "2") << "\n"; 
    // Does not work, because it's an invalid use for the function f, we wrote that for things which are addable.
    // How did we try to indicate this intention of "addability" of the arguments ?
    // Answer : We didn't!
    // If the function had been 50 lines instead of 1, the real error would be very hard to
    // decipher. There is an assumption regarding incoming arguments in our function template,
    // and we did not specify that assumption anywhere. How does one indicate such constraints ?
    // Answer(C++20) : concepts
    // Answer(C++ < C++20) : std::enable_if, type_traits and some acrobatic programming.
}

