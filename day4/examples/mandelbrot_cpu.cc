#include "CountingIterator.hh"
#include <algorithm>
#include <chrono>
#include <complex>
#include <execution>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void save_pgm(std::string filename, size_t width, size_t height,
    std::vector<unsigned char> data)
{
    std::ofstream fout { filename };
    fout << "P2\n"
         << width << " " << height << " 255\n";
    for (size_t row = 0; row < height; ++row) {
        for (size_t col = 0; col < width; ++col) {
            fout << (col ? " " : "")
                 << static_cast<unsigned>(data[row * width + col]);
        }
        fout << "\n";
    }
    fout.close();
}

auto mandel(size_t width, size_t height) -> std::vector<unsigned char> 
{
    double aspect = static_cast<double>(width) / height;
    std::vector<unsigned char> ans(width * height, 0);
    CountingIterator<size_t> beg { 0 }, end { width * height };
    std::transform(std::execution::par, beg, end,
        ans.begin(), [=](size_t index) {
            double myrow = index / width;
            double mycol = index % width;
            myrow /= height;
            mycol /= width;
            std::complex<double> z0 { aspect * (2 * mycol - 1) - 0.5,
                2 * myrow - 1 };
            unsigned char lim = 255;
            double mag = 0;
            decltype(z0) z;
            do {
                z = z * z + z0;
                mag = norm(z);
            } while (lim-- && mag < 4.0);
            return lim;
        });
    return ans;
}

auto main(int argc, char* argv[]) -> int
{
    if (argc != 3) {
        std::cerr << "Usage:\n"
                  << argv[0] << " width height\n";
        return 1;
    }
    size_t width = std::stoul(argv[1]);
    size_t height = std::stoul(argv[2]);
    using namespace std::chrono;
    auto t0 = steady_clock::now();
    auto img = mandel(width, height);
    auto t1 = steady_clock::now();
    std::cout << "calculation took " << duration_cast<milliseconds>(t1 - t0).count() << " milliseconds\n";
    save_pgm("output.pgm", width, height, img);
}
