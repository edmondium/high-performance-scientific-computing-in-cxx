#include <iostream>
#include <cxx20format>

auto main() -> int
{
    class A {
        char c;
        double x;
        int d;
    };
    auto report = [](std::string_view tpname, size_t size, size_t alignment) {
        std::cout << format("Type = {:>16}, alignment = {:>3}, size = {:<4}\n",
            tpname, alignment, size);
    };
    report("char", sizeof(char), alignof(char));
    report("int", sizeof(int), alignof(int));
    report("short", sizeof(short), alignof(short));
    report("float", sizeof(float), alignof(float));
    report("double", sizeof(double), alignof(double));
    report("long", sizeof(long), alignof(long));
    report("long double", sizeof(long double), alignof(long double));
    report("long long", sizeof(long long), alignof(long long));
    report("(class)A", sizeof(A), alignof(A));
}
