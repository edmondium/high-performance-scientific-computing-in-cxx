#include <concepts>
template <int X>
concept PowerOfTwo = (X != 0 && (X & (X-1)) == 0);
template <class T>
concept Number = std::integral<T> || std::floating_point<T>;
template <class T, int N>
requires Number<T> and PowerOfTwo<N>
struct MyMatrix {

};

auto main() -> int
{
    auto m = MyMatrix<double, 16>{};
}

