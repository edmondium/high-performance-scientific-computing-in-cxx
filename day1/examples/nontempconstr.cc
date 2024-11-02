#include <string>
#include <iostream>

template <class N> concept Number = std::integral<N> || std::floating_point<N>;
template <class N> concept Integer = Number<N> && std::integral<N>;

template <class T>
struct ClassTemp {
    constexpr auto operator++() noexcept -> std::enable_if_t<std::is_integral_v<T>, ClassTemp&> { ++obj; return *this; }
    //constexpr auto nonTemplateMemberFunction() noexcept -> ClassTemp& requires Integer<T> { ++obj; return *this; }
    auto other() -> std::string { return "something else"; }
    constexpr auto val() const -> T { return obj; }
    T obj{};
};

auto main() -> int
{
    ClassTemp<double> x{};
    //std::cout << (++x).val() << "\n";
    std::cout << x.other() << "\n";
}

