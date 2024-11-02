#include <string>
#include <iostream>

template <class N> concept Number = std::is_integral_v<N> or std::is_floating_point_v<N>;
template <class N> concept Integer = Number<N> and std::is_integral_v<N>;

template <class T>
struct ClassTemp {
    //auto nonTemplateMemberFunction() -> std::enable_if_t<std::is_integral_v<T>, int> { return 42; }
    constexpr auto nonTemplateMemberFunction() const noexcept -> int requires Integer<T> { return 42; }
    auto other() -> std::string { return "something else"; }
};

auto main() -> int
{
    ClassTemp<double> x;
    //std::cout << x.nonTemplateMemberFunction() << "\n";
    std::cout << x.other() << "\n";
}

