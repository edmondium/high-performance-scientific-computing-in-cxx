#ifndef NAIVE_VEC_HH
#define NAIVE_VEC_HH

#include <cassert>
#include <vector>

namespace HPCXX {
template <typename T>
class vec {
    std::vector<T> dat;

public:
    vec(size_t n)
        : dat(n)
    {
    }
    auto operator[](size_t i) const -> T { return dat[i]; }
    auto operator[](size_t i) -> T& { return dat[i]; }
    auto size() const -> size_t { return dat.size(); }
    auto begin() { return dat.begin(); }
    auto end() { return dat.end(); }
    auto begin() const { return dat.begin(); }
    auto end() const { return dat.end(); }
};

template <typename T>
auto operator+(const vec<T>& v1, const vec<T>& v2) -> vec<T>
{
    assert(v1.size() == v2.size());
    auto ans = v1;
    for (size_t i = 0; i < ans.size(); ++i)
        ans[i] += v2[i];
    return ans;
}

template <typename T>
auto operator*(const T& t, const vec<T>& V) -> vec<T>
{
    auto ans = V;
    for (size_t i = 0; i < ans.size(); ++i)
        ans[i] *= t;
    return ans;
}
}

#endif
