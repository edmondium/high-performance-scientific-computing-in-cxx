#include "CountingIterator.hh"
#include "pngwriter.h"
#include <chrono>
#include <complex>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <execution>
#include <string>
#include <vector>

using image_representation = std::vector<unsigned char>;

void save_png(std::string ofile, int width, int height, const image_representation& img)
{
    pngwriter output { width, height, 0.0, ofile.c_str() };
    for (auto i = 1; i <= height; ++i) {
        for (auto j = 1; j <= width; ++j) {
            auto c = img[i * width + j];
            output.plot(j, i, c / 255.0, c / 255.0, (c + 50) / 255.0);
        }
    }
    output.close();
}

std::vector<unsigned char> mandel(int width, int height)
{
    double aspect = static_cast<double>(width) / height;
    std::vector<unsigned char> ans(width * height, 0);
    CountingIterator<decltype(width)> beg { 0 }, end { width * height };
    std::transform(std::execution::seq,
        beg, end,
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

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cerr << "Usage:\n"
                  << argv[0] << " width height\n";
        return 1;
    }
    int width = std::stoi(argv[1]);
    int height = std::stoi(argv[2]);
    auto t0 = std::chrono::high_resolution_clock::now();
    auto img = mandel(width, height);
    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << "Generation of Mandelbrot set for image size " << width << " x " << height << " took "
              << std::chrono::duration<double>(t1 - t0).count() << " seconds\n";
    save_png("output.png", width, height, img);
}
