#include <algorithm>
#include <array>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>

auto main(int argc, char* argv[]) -> int
{
    // Generate data
    constexpr unsigned arraySize = 65536;
    std::array<int, arraySize> data;

    auto gen = [
                engine = std::mt19937_64(std::random_device{}()), 
                dist = std::uniform_int_distribution<>{0, 255 } 
               ]()mutable
    {
        return dist(engine);
    };
    std::generate(data.begin(), data.end(), gen);

    // !!! With this, the next loop runs faster
    // To enable sorting, just pass any argument on the command line
    if (argc > 1)
        std::sort(data.begin(), data.end());

    auto start = std::chrono::high_resolution_clock::now();
    long sum1 = 0, sum2 = 0, sum3 = 0;
    auto totiter = 100000U;
    for (auto i = 0U; i < totiter; ++i) {
	if (i % 5000U == 0U) std::cout << "Wait... (remaining iterations = " << totiter - i << ")\n";
        // Primary loop
        for (auto c = 0U; c < arraySize - 1; ++c) {
            if (data[c] < 100)
                sum1 += (data[c] + data[c + 1]) / 2;
            else if (data[c] < 200)
                sum2 += (data[c] + data[c + 1]) / 2;
            else
                sum3 += (data[c] + data[c + 1]) / 2;
        }
    }

    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsedTime = std::chrono::duration<double>(t_end - start).count();

    std::cout << "Elapsed time = " << elapsedTime << " seconds\n";
    std::cout << "sums = " << sum1 << ", " << sum2 << ", " << sum3 << "\n";
}
