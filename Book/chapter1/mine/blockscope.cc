// examples/blockscope.cc

#include <iostream>
#include <string>

int main()
{
    std::string x{"three"};
    {
        std::cout << x << "\n";
        double x = 488332;
        std::cout << x << "\n";
        {
            x = x - 1;
            {
                x = x / 3;
                std::cout << x << "\n";
            }
            {
                std::string x{"four"};
                std::cout << x << "\n";
            }
        }
    }
    std::cout << x << "\n";
}
