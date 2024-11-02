#include <iostream>

int main()
{
    class A {
        char c;
        double x;
        int d;
    };
    std::cout << "Alignment and size of char " << alignof(char) << ", " << sizeof(char) << "\n";
    std::cout << "Alignment and size of int  " << alignof(int) << ", " << sizeof(int) << "\n";
    std::cout << "Alignment and size of short " << alignof(short) << ", " << sizeof(short) << "\n";
    std::cout << "Alignment and size of float " << alignof(float) << ", " << sizeof(float) << "\n";
    std::cout << "Alignment and size of double " << alignof(double) << ", " << sizeof(double) << "\n";
    std::cout << "Alignment and size of long " << alignof(long) << ", " << sizeof(long) << "\n";
    std::cout << "Alignment and size of long double " << alignof(long double) << ", " << sizeof(long double) << "\n";
    std::cout << "Alignment and size of long long " << alignof(long long) << ", " << sizeof(long long) << "\n";
    std::cout << "Alignment and size of A " << alignof(A) << ", " << sizeof(A) << "\n";
}
