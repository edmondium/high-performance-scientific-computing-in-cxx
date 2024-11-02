#ifndef XTMP_VEC_HH
#define XTMP_VEC_HH

#include <cassert>
#include <vector>

namespace HPCXX {
/*
 * The base class of our expressions does not need any more capabilities than
 * simply giving us back the inherited objects when asked.
 */
template <typename X>
struct vecxpr {
    auto operator~() noexcept -> X& { return *static_cast<X*>(this); }
    auto operator~() const -> const X& { return *static_cast<const X*>(this); }
};

template <typename T>
class vec : public vecxpr<vec<T>> {
    std::vector<T> dat;
public:
    using value_type = T;
    vec(size_t n) : dat(n)
    {
    }
    auto operator[](size_t i) const -> const T { return dat[i]; }
    auto operator[](size_t i) -> T& { return dat[i]; }
    auto size() const -> size_t { return dat.size(); }
    auto n_ops() const -> size_t { return 0; }
    template <class X>
    auto operator=(const vecxpr<X>& y) -> vec&
    {
        for (size_t i = 0; i < (~y).size(); ++i)
            dat[i] = (~y)[i];
        return *this;
    }

    auto begin() const { return dat.begin(); }
    auto begin() { return dat.begin(); }
    auto end() const { return dat.end(); }
    auto end() { return dat.end(); }
};

template <typename T1, typename T2>
class vecsum : public vecxpr<vecsum<T1, T2>> {
    const T1& lhs;
    const T2& rhs;

public:
    using value_type = typename T1::value_type;
    vecsum(const vecxpr<T1>& l, const vecxpr<T2>& r)
        : lhs{ (~l) }
        , rhs{ (~r) }
    {
        assert((~l).size() == (~r).size());
    }
    const auto operator[](size_t i) const { return (~lhs)[i] + (~rhs)[i]; }
    auto size() const -> size_t { return (~lhs).size(); }
    inline auto n_ops() const -> size_t { return 1 + (~lhs).n_ops() + (~rhs).n_ops(); }
};

template <typename T1, typename T2>
auto operator+(const vecxpr<T1>& v1, const vecxpr<T2>& v2) -> vecsum<T1, T2> const
{
    return vecsum<T1, T2>{ (~v1), (~v2) };
}

template <typename T>
class vecscl : public vecxpr<vecscl<T>> {
public:
    using value_type = typename T::value_type;
    vecscl(const value_type& l, const vecxpr<T>& r)
        : lhs{ l }
        , rhs{ (~r) }
    {
    }
    const auto operator[](size_t i) const { return lhs * rhs[i]; }
    auto size() const -> size_t { return rhs.size(); }
    auto n_ops() const -> size_t { return 1 + rhs.n_ops(); }

private:
    const value_type& lhs;
    const T& rhs;
};

template <typename T>
auto operator*(const typename T::value_type& s, const vecxpr<T>& v) -> const vecscl<T>
{
    return vecscl<T>{ s, v };
}
}

#endif

