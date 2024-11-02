#include <chrono>
#include <iomanip>
#include <iostream>
#include <vector>

auto main() -> int
{
    constexpr size_t size = 2 << 26;
    std::vector<long> A(size, 0);
    int tot = 0;
    size_t nrep = 10;
    for (size_t step = 1; step <= 2048; step *= 2) {
        auto start = std::chrono::high_resolution_clock::now();
        for (size_t rep = 0; rep < nrep; ++rep) {
            for (size_t i = 0; i < size; i += step)
                A[i]++;
        }
        auto end = std::chrono::high_resolution_clock::now();
        tot += A[size / 2 + step];
        std::cout << std::setw(4) << std::right << step << " "
                  << std::chrono::duration<double>(end - start).count() / nrep << "\n";
    }
    std::cout << "Total = " << tot << "\n";
}
