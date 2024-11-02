#include <tbb/parallel_invoke.h>
#include <iostream>
#include <chrono>
#include <thread>

void function1()
{
    for (int i=0;i<10;++i) {
        std::cout << '1' << std::endl;
        std::this_thread::sleep_for(std::chrono::duration<double>(1.0/(1+rand() % 15)));        
    }
}
void function2()
{
    for (int i=0;i<10;++i) {
        std::cout << '2' << std::endl;
        std::this_thread::sleep_for(std::chrono::duration<double>(1.0/(1+rand() % 15)));        
    }
}

auto main() -> int
{
    tbb::parallel_invoke(function1, function2);
    std::cout << "\n";
}

