#include <cstddef>
class MyStruct {
public:
    auto value() const { return val; }
    void value(double x) { val = x; }

private:
    double val = 0;
};

auto foo(size_t howmanytimes)
{
    MyStruct s;
    for (size_t i = 0; i < howmanytimes; ++i)
        s.value(s.value() + 1);
    return s.value();
}

auto bar(size_t howmanytimes)
{
    double val = 0;
    for (size_t i = 0; i < howmanytimes; ++i)
        val += 1;
    return val;
}
