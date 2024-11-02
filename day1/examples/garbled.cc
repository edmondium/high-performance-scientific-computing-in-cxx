#include <iostream>
#include <omp.h>

auto main() -> int
{
    #pragma omp parallel for
    for (auto i = 0UL; i < 16UL; ++i) {
       std::cout << "counter = " << i 
         << " on thread " 
         << omp_get_thread_num() << "\n";
    }
}

