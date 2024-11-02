#include <type_traits>
template <int X>
concept PowerOfTwo = (X != 0 && (X & (X-1)) == 0);
template <class T>
concept Number = std::is_integral_v<T> || std::is_floating_point_v<T>;
template <class T, int N> requires Number<T> and PowerOfTwo<N>
struct MyMatrix {

};

auto main() -> int
{
    auto m = MyMatrix<double*, 16>{};
}

