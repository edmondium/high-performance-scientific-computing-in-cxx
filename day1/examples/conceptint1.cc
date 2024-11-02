template <int X>
concept PowerOfTwo = (X != 0 && (X & (X-1)) == 0);

template <class T, int N> requires PowerOfTwo<N>
struct MyMatrix {

};

auto main() -> int
{
    auto m = MyMatrix<double, 17>{};
}

