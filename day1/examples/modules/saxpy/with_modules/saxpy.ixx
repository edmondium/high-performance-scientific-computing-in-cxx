/* We are using #includes rather than imports
to be able to compile with gcc. Clang works
fine with the imports of STL headers. GCC,
even after generating header units with
-xc++-system-header crashes with an internal
compiler error.
*/

module;
#include <algorithm>
#include <span>
export module saxpy;

template <class T>
concept Number = std::floating_point<T>
              or std::integral<T>;

export template <Number T>
auto saxpy(T a, std::span<const T> x,
           std::span<const T> y,
           std::span<T> z)
{
    std::transform(x.begin(), x.end(),
                   y.begin(), z.begin(),
        [a](T X, T Y) {
            return a * X + Y;
        });
}

