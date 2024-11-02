#ifndef QUADDOUBLE_HH
#define QUADDOUBLE_HH

#include <immintrin.h>
#include <cassert>

auto get_alignment(const void* ptr) -> unsigned
{
    auto n = reinterpret_cast<unsigned long>(ptr);
    return (-n) & n;
}
union alignas(32) QuadDouble {
    __m256d mm;
    double d[4];
    QuadDouble(__m256d oth) : mm{oth} {}
    QuadDouble() : mm{_mm256_setzero_pd()} {}
    QuadDouble(double x) : mm{_mm256_broadcast_sd(&x)} {}
    constexpr QuadDouble(double x, double y, double z=0., double t=0.)
        : d{x,y,z,t} {}
    void aligned_load(const double * v) {
        assert(get_alignment(v) >= 32);
        mm = _mm256_load_pd(v);
    }
    void aligned_store(double *v) {
        assert(get_alignment(v) >= 32);
        _mm256_store_pd(v, mm);
    }
    void unaligned_load(const double * v) {
        mm = _mm256_loadu_pd(v);
    }
    void unaligned_store(double *v) {
        _mm256_storeu_pd(v, mm);
    }
    auto operator[](unsigned i) const -> double
    { 
        return d[i%4];
    }
    auto operator[](unsigned i) -> double& { return d[i % 4]; }
    auto horizontal_add() const -> double
    {
        return d[0]+d[1]+d[2]+d[3];
    }
    void uniform(double x) {
        mm = _mm256_broadcast_sd(&x);
    }
};
inline auto operator+(QuadDouble a, QuadDouble b) -> QuadDouble
{
    return _mm256_add_pd(a.mm, b.mm);
}
inline auto operator-(QuadDouble a, QuadDouble b) -> QuadDouble
{
    return _mm256_sub_pd(a.mm, b.mm);
}
inline auto operator*(QuadDouble a, QuadDouble b) -> QuadDouble
{
    return _mm256_mul_pd(a.mm, b.mm);
}
inline auto operator/(QuadDouble a, QuadDouble b) -> QuadDouble
{
    return _mm256_div_pd(a.mm, b.mm);
}

#endif

