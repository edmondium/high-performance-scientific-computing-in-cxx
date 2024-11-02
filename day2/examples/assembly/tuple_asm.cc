#include <array>
#include <tuple>

struct alignas(64) four {
    std::array<double, 4> dat;
};

//using argtype = std::tuple<double, double, double, double>;
//using argtype = std::array<double, 4>;
using argtype = four;
template <int N>
auto get(four f) { return std::get<N>(f.dat); }

auto square(const argtype& num) -> argtype
{
    return { get<0>(num) * get<0>(num),
        get<1>(num) * get<1>(num),
        get<2>(num) * get<2>(num),
        get<3>(num) * get<3>(num) };
}

