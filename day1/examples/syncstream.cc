#include <iostream>
#include <omp.h>
#include <syncstream>

auto main(int argc, char* argv[]) -> int
{
#pragma omp parallel for
    for (auto i = 0UL; i < 16UL; ++i) {
        std::osyncstream { std::cout } << "counter = " << i
                                       << " on thread "
                                       << omp_get_thread_num() << "\n";
    }
}
