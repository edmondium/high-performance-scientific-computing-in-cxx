// #include <concepts>
#include <limits>
#include <print>
#include <stdfloat>
#include <typeinfo>

template <class T>
auto showprops(std::string_view name)
{
    using std::numeric_limits;
    std::print("{: <20}{: <12}{: <30}{: <30}{: <30}\n",
        name,
        typeid(T).name(),
        numeric_limits<T>::min(), numeric_limits<T>::max(),
        numeric_limits<T>::epsilon());
}
auto main() -> int
{
    std::print("Floating point type characteristics...\n");
    std::print("{: ^16}{: ^12}{: ^30}{: ^30}{: ^30}\n",
        "Name", "typeid", "Min", "Max", "Epsilon");
    showprops<double>("double");
    showprops<std::float64_t>("std::float64_t");
    showprops<float>("float");
    showprops<std::float32_t>("std::float32_t");
    showprops<std::float16_t>("std::float16_t");
    showprops<std::bfloat16_t>("std::bfloat16_t");
    //  static_assert(std::same_as<std::float32_t, float>);
    //  static_assert(std::same_as<std::float64_t, double>);
}
