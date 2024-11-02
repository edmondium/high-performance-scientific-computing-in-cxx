#ifndef SIMD_WRAPPER_HH
#define SIMD_WRAPPER_HH
#include <algorithm>
#include <cassert>
#include "cache_props.hh"
#if defined USE_SIMD && USE_SIMD
#include <xsimd/xsimd.hpp>
#endif
#if defined USE_SIMD && USE_SIMD
using b_type = xsimd::simd_type<double>;
namespace simdlib = xsimd;
#else
#include <array>
#include <iostream>
namespace simdlib {
constexpr auto simd_reg_width_in_bytes = 32ul;
template <typename T>
constexpr auto n_fits_in_simd_reg = simd_reg_width_in_bytes / sizeof(T);
template <typename T>
struct alignas(simd_reg_width_in_bytes) simd_type {
    static constexpr auto size = n_fits_in_simd_reg<T>;
    std::array<T, size> dat;
    auto operator[](size_t i) const { return dat[i]; }
    auto& operator[](size_t i) { return dat[i]; }
};
template <typename T>
simd_type<T> load_unaligned(const T* ptr)
{
    simd_type<T> buf;
    std::copy(ptr, ptr + buf.size, std::begin(buf.dat));
    return buf;
}
template <typename T>
simd_type<T> load_aligned(const T* ptr)
{
    [[maybe_unused]] unsigned long n = reinterpret_cast<unsigned long>(ptr);
    assert(((-n) & n) >= (sizeof(T) * simd_type<T>::size));
    return load_unaligned(ptr);
}
template <typename T>
void store_unaligned(T* ptr, const simd_type<T>& v)
{
    std::copy(std::begin(v.dat), std::end(v.dat), ptr);
}
template <typename T>
void store_aligned(T* ptr, const simd_type<T>& v)
{
    [[maybe_unused]] unsigned long n = reinterpret_cast<unsigned long>(ptr);
    assert(((-n) & n) >= (sizeof(T) * v.size));
    store_unaligned(ptr, v);
}
template <typename T>
simd_type<T> set_simd(const T t)
{
    simd_type<T> buf;
    std::fill_n(std::begin(buf.dat), buf.size, t);
    return buf;
}
template <typename T>
simd_type<T> operator+(const simd_type<T>& lhs, const simd_type<T>& rhs)
{
    simd_type<T> buf;
    std::transform(std::begin(lhs.dat), std::end(lhs.dat),
        std::begin(rhs.dat),
        std::begin(buf.dat), std::plus<T>());
    return buf;
}
template <typename T>
simd_type<T> operator*(const simd_type<T>& lhs, const simd_type<T>& rhs)
{
    simd_type<T> buf;
    std::transform(std::begin(lhs.dat), std::end(lhs.dat),
        std::begin(rhs.dat),
        std::begin(buf.dat), std::multiplies<T>());
    return buf;
}
template <typename T>
simd_type<T> operator-(const simd_type<T>& lhs, const simd_type<T>& rhs)
{
    simd_type<T> buf;
    std::transform(std::begin(lhs.dat), std::end(lhs.dat),
        std::begin(rhs.dat),
        std::begin(buf.dat), std::minus<T>());
    return buf;
}
template <typename T>
simd_type<T> fma(const simd_type<T>& x, const simd_type<T>& y, const simd_type<T> & z)
{
    simd_type<T> buf;
    for (int i = 0; i < 4; ++i) buf[i] = x[i] * y[i] + z[i];
    return buf;
}
}
using b_type = simdlib::simd_type<double>;
template <typename T>
std::ostream& operator<<(std::ostream& os, const simdlib::simd_type<T>& b)
{
    os << "[";
    for (size_t i = 0ul; i < b.size; ++i)
        os << b[i] << ", ";
    os << "]";
    return os;
}

#endif
constexpr auto bsize = b_type::size;

#endif
