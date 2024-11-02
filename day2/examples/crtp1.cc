#include <iostream>
#include <string>

template <class ClassWithName>
class Named {
public:
    auto get_name() const -> std::string { return static_cast<ClassWithName const*>(this)->get_name_impl(); }
    auto version() const -> double { return 1.0; }
};

class Acetyl : public Named<Acetyl> {
public:
    auto get_name_impl() const -> std::string { return "Acetyl"; }
};

class HBMM : public Named<HBMM> {
public:
    auto get_name_impl() const -> std::string { return "HBMM"; }
};

auto main() -> int
{
    Acetyl a;
    HBMM b;
    std::cout << "Calling get_name on a returns : " << a.get_name() << '\n';
    std::cout << "Calling get_name on b returns : " << b.get_name() << '\n';
    std::cout << "Their versions are " << a.version() << " and " << b.version() << '\n';
}
