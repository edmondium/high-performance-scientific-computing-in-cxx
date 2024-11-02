#pragma once

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

    auto operator()(size_t i, size_t j) -> T&
    {
        return v[i * nc + j];
    }
    auto operator()(size_t i, size_t j) const -> T
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
        auto operator[](size_t i) const -> U
        {
            return orig[offst + i * strd];
        }
    };
    auto operator[](size_t i) -> row_t<T>
    {
        return row_t<T>(v, i * nc, 1);
    }
};

