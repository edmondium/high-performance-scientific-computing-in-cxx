#include <chrono>
#include <iostream>
#include <vector>

template <class T>
class array2d {
    std::vector<T> v;
    size_t nc { 0 }, nr { 0 };

public:
    array2d(size_t i, size_t j)
        : v(i * j, T {})
        , nc(j)
        , nr(i)
    {
        auto scl = 1.0 / (i * j);
        // simple non zero init. Init values are not the point here.
        for (auto k = 0ul; k < i * j; ++k)
            v[k] = 1 + 3.2 * scl * k;
    }

    auto operator()(size_t i, size_t j) -> T&
    {
        return v[i * nc + j];
    }
    auto operator()(size_t i, size_t j) const -> T
    {
        return v[i * nc + j];
    }
};

auto main() -> int
{
    double sum = 0.;
    for (size_t size = 10; size < 3000; ++size) {
        array2d<double> A(size, size);
        auto t0 = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < i; ++j) {
                auto tmp = A(i, j);
                A(i, j) = A(j, i);
                A(j, i) = tmp;
            }
            sum += A(size / 4, size / 5);
        }
        auto t1 = std::chrono::high_resolution_clock::now();
        std::cout << size << "\t" << std::chrono::duration<double>(t1 - t0).count() / (size * size) << "\n";
        if (size % 100 == 0)
            std::cerr << "Done with size " << size << "\n";
    }
}
