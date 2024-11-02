#include <iomanip>
#include <iostream>
#include <list>
#include <string>

// A "template function" to determine if the typename given as template
// argument has a member function called size()
template <typename T>
struct has_memfunc_size {
    // If a type U has a member function size(), the decltype resolves to something
    // concrete, and the following overload for test is found.
    template <typename U>
    static auto test(decltype(std::declval<U>().size())* x) -> char;

    // For all cases where the above template does not match, the following has to
    // match. Note that in neither case do we provide any implementation. We are
    // just playing the template matching rules to get information. Depending on
    // which overload is selected by the compiler, the return type is either char
    // or long.
    template <typename U>
    static auto test(...) -> long;

    // We can now declare a static constexpr variable value, and initialize
    // it to true or false by checking if the size of the return value of test<T>
    // is the size of char.
    static constexpr const bool value = sizeof(test<T>(0)) == sizeof(char);
};

auto main() -> int
{
    // And, here is how we can use our template function to check if a given type has
    // a member function called size():
    std::cout << "std::list has a size element : " << std::boolalpha << has_memfunc_size<std::list<int>>::value << "\n";
    std::cout << "std::string has a size element : " << std::boolalpha << has_memfunc_size<std::string>::value << "\n";
    std::cout << "int has a size element : " << std::boolalpha << has_memfunc_size<int>::value << "\n";
}
