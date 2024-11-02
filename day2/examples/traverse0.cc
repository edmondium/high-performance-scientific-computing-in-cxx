#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

auto main() -> int
{
    size_t N = 10000;
    std::vector<int> A(N * N, 0);
    // Row major
    std::cout << "Row major traversing ... \n";
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            A[i * N + j] += i + j;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Middle element is " << A[N * N / 2] << "\n";
    std::cout << "Traversing took "
              << std::chrono::duration<double>(end - start).count() << " seconds \n\n";
    // Column major
    std::cout << "Column major traversing ... \n";
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            A[j * N + i] += i + j;
        }
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Middle element is " << A[N * N / 2] << "\n";
    std::cout << "Traversing took "
              << std::chrono::duration<double>(end - start).count() << " seconds \n\n";
    // Random order
    std::cout << "Initializing position array with shuffled indexes\n";
    std::vector<int> pos(N * N);
    std::iota(pos.begin(), pos.end(), 0);
    std::shuffle(pos.begin(), pos.end(), std::mt19937_64 {});
    std::cout << "Shuffling done. Access time measurement for indirect array ...\n";
    start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N * N; ++i) {
        A[pos[i]] += pos[i];
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Middle element is " << A[N * N / 2] << "\n";
    std::cout << "Traversing took "
              << std::chrono::duration<double>(end - start).count() << " seconds \n\n";
}
