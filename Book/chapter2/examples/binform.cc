#include <iostream>
#include <bitset>
#include <bit>
#include <cstddef>
#include <iomanip>

auto bits(auto var)
{
    unsigned long bytes{0UL};
    std::byte * in = reinterpret_cast<std::byte *>(&var);
    std::byte * out = reinterpret_cast<std::byte *>(&bytes);
    std::copy(in, in + sizeof(var), out);
    return std::bitset<8*sizeof(decltype(var))>(bytes) ;
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

void showbits(auto var)
{
    std::cout << "bits for " << var << " with non-floating point type : " << bits(var) << "\n";
}

int main()
{
    showbits(1);
    showbits(1U - 2U);
    showbits(-1);
    showbits(1.0);
    showbits(1.25);
    showbits(1.25F);
    showbits(1.5);
    showbits(1.75);
    showbits(2.0);
    showbits(4.0);
    showbits(8.0);
    showbits(0.0);
    showbits(-0.0);
    std::cout << "-0.0 == 0.0 is " << std::boolalpha << (-0.0 == 0.0) << "\n\n";
    showbits(1.0e-100);
    std::cout << "1.0e-100 == 0.0 is " << std::boolalpha << (1.0e-100 == 0.0) << "\n\n";
    showbits(8UL);
}

