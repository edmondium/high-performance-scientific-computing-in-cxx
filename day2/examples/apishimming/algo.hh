#include <type_traits>
#include <cstddef>

template <class T>
concept hasAPI = requires( T x ) {
    { x.calculateFast() };
    { x.helper() };
};

// Now we want to have two versions of the algorithm depending on whether
// the target class has the required API or not. If the class C has
// functions helper() and calculateFast(), we want to use them. If not,
// we should fall back to the (perhaps slower) calculate() function.
// We can implement two overloads of algo using the requires clauses
// as before, but, just for the fun of it, here is another way to use
// teh concept defined above. Concepts are boolean expressions of templates.

template <class C> auto algo(C && x) -> size_t
{
    if constexpr (hasAPI<C>) {
        x.helper();
        return x.calculateFast();
    } else {
        return x.calculate();
    }
}


