#include <iostream>
#include <vector>
template <class T>
class array2d {
    std::vector<T> v;
    size_t nc{ 0 }, nr{ 0 };

public:
    array2d(size_t i, size_t j)
        : v(i * j, T{})
        , nc(j)
        , nr(i)
    {
    }
    auto nrows() const noexcept -> size_t { return nr; }
    auto ncols() const noexcept -> size_t { return nc; }
    auto operator[](size_t i, size_t j) -> T&
    {
        return v[i * nc + j];
    }
    auto operator[](size_t i, size_t j) const -> const T&
    {
        return v[i * nc + j];
    }
    template <class U>
    struct row_t {
        std::vector<U>& orig;
        size_t offst, strd;
        explicit row_t(std::vector<U>& vv,
            size_t i, size_t st)
            : orig(vv)
            , offst(i)
            , strd(st)
        {
        }
        auto operator[](size_t i) -> U&
        {
            return orig[offst + i * strd];
        }
        auto operator[](size_t i) const -> const U&
        {
            return orig[offst + i * strd];
        }
    };
    auto operator[](size_t i) -> row_t<T>
    {
        return row_t<T>(v, i * nc, 1);
    }
};

auto main() -> int
{
    array2d<double> A{10UL, 4UL};
    for (auto i = 0UL; i < A.nrows(); ++i) {
        for (auto j = 0UL; j < A.ncols(); ++j) {
            std::cout << A[i, j] << "\t";
        }
        std::cout << "\n";
    }
}

