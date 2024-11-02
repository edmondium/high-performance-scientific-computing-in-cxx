#include <bitset>
#include <cstddef>
#include <iomanip>
#include <iostream>

namespace cxx_course {
using byte = unsigned char;

template <class T>
auto bits(T var)
{
    std::remove_cv_t<std::remove_reference_t<T>> loc { var };
    unsigned long bytes { 0UL };
    byte* in = reinterpret_cast<byte*>(&loc);
    byte* out = reinterpret_cast<byte*>(&bytes);
    std::copy(in, in + sizeof(loc), out);
    return std::bitset<8 * sizeof(decltype(loc))>(bytes);
}

void showbits(double var)
{
    std::cout << "bits for double value " << var << "\n";
    auto b = bits(var).to_string();
    std::cout << "raw = " << b << "\n";
    std::cout << "sign  exponent          mantissa\n"
              << std::setw(6) << std::left << b[0]
              << std::setw(16) << std::left << b.substr(1UL, 11)
              << "  " << b.substr(12) << "\n\n";
}

void showbits(float var)
{
    std::cout << "bits for float value " << var << "\n";
    auto b = bits(var).to_string();
    std::cout << "raw = " << b << "\n";
    std::cout << "sign  exponent          mantissa\n"
              << std::setw(6) << std::left << b[0]
              << std::setw(16) << std::left << b.substr(1UL, 8)
              << "  " << b.substr(9) << "\n\n";
}

template <class T>
void showbits(T var)
{
    std::cout << "bits for " << var << " with non-floating point type : " << bits(var) << "\n";
}

}
