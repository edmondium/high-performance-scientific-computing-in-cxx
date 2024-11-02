#include "pngwriter.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thrust/complex.h>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/transform.h>

using thrust::complex;
using image_representation = typename thrust::host_vector<unsigned char>;

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

image_representation mandel(size_t width, size_t height)
{
    thrust::device_vector<unsigned char> res(width * height, 0);
    double aspect = static_cast<double>(width) / height;
    thrust::counting_iterator<size_t> indexes{0UL};
    thrust::transform(indexes, indexes + width * height,
        res.begin(), [=] __host__ __device__(size_t index) {
            double myrow = index / width;
            double mycol = index % width;
            myrow /= height;
            mycol /= width;
            thrust::complex<double> z0 { aspect * (2 * mycol - 1) - 0.5,
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
    thrust::host_vector<unsigned char> ans = res;
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
