#include <print>
#include <string>

class Named {
public:
    template <class Self>
    auto get_name(this Self&& self) -> std::string
    {
        return self.get_name_impl();
    }
    auto version() const -> double { return 1.0; }
};

class Acetyl : public Named {
public:
    auto get_name_impl() const -> std::string { return "Acetyl"; }
};

class HBMM : public Named {
public:
    auto get_name_impl() const -> std::string { return "HBMM"; }
};

auto main() -> int
{
    Acetyl a;
    HBMM b;
    std::print("Calling get_name on a returns : {}\n", a.get_name());
    std::print("Calling get_name on b returns : {}\n", b.get_name());
    std::print("Their versions are {} and {}\n", a.version(), b.version());
}
