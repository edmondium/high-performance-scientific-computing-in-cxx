template <typename FPType, unsigned N>
struct alignas(sizeof(FPType) * N) Vec {
    FPType d[N];
    auto operator+(Vec x) const
    {
        Vec ans;
        for (int i = 0; i < N; ++i)
            ans.d[i] = d[i] + x.d[i];
        return ans;
    }
    auto operator*(FPType x) const
    {
        Vec ans;
        for (int i = 0; i < N; ++i)
            ans.d[i] = d[i] * x;
        return ans;
    }
};
template <typename FPType, unsigned N>
auto operator*(FPType a, const Vec<FPType, N> & x) { return x * a; }

using FT = float;
constexpr auto sz = 16UL;
auto f(FT a, const Vec<FT, sz> & x, const Vec<FT, sz> & y)
{
    return a * x + y;
}
