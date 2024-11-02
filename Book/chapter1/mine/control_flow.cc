#include <iostream>

void say_hello()
{
    std::cout << "Hello!\n";
}

auto add(int input1, int input2) -> int
{
    return input1 + input2;
}

auto sub(int input1, int input2) -> int
{
    return input1 - input2;
}

auto main() -> int
{
    auto v1 = add(34552, 88112);
    auto v2 = add(v1, sub(335, 88112));
    say_hello();
    std::cout << "v1 has value : " << v1 << "\n";
    std::cout << "v2 has value : " << v2 << "\n";
}

