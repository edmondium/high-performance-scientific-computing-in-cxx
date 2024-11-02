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
using CI = thrust::counting_iterator<size_t>;

void save_png(std::string ofile, size_t width, size_t height, const image_representation& img)
{
    pngwriter output { static_cast<int>(width), static_cast<int>(height), 0.0, ofile.c_str() };
    for (auto i = 0UL; i < height; ++i) {
        for (auto j = 0UL; j < width; ++j) {
            auto c = img[i * width + j];
            output.plot(j + 1UL, i + 1UL, c / 255.0, c / 255.0,
			    (static_cast<unsigned long>(c) + 50UL) / 255.0);
        }
    }
    output.close();
}

auto mandel(size_t width, size_t height) -> image_representation
{
    thrust::device_vector<unsigned char> res(width * height, 0);
    double aspect = static_cast<double>(width) / height;
    CI beg { 0UL };
    CI end { beg + width * height };
    thrust::transform(beg, end,
        res.begin(), [=] __host__ __device__(size_t index) {
            double myrow = index / width;
            double mycol = index % width;
            myrow /= height;
            mycol /= width;
            complex<double> z0 { aspect * (2 * mycol - 1) - 0.5,
                2 * myrow - 1 };
            unsigned char lim = 255;
            double mag = 0;
            decltype(z0) z{};
            do {
                z = z * z + z0;
                mag = norm(z);
            } while (lim-- && mag < 4.0);
            return lim;
        });
    thrust::host_vector<unsigned char> ans = res;
    return ans;
}

auto main(int argc, char* argv[]) -> int
{
    namespace sc = std::chrono;
    if (argc != 3) {
        std::cerr << "Usage:\n"
                  << argv[0] << " width height\n";
        return 1;
    }
    auto width = std::stoul(argv[1]);
    auto height = std::stoul(argv[2]);
    auto t0 = sc::high_resolution_clock::now();
    auto img = mandel(width, height);
    auto t1 = sc::high_resolution_clock::now();
    std::cout << "Generation of Mandelbrot set for image size " << width << " x " << height << " took "
              << sc::duration<double>(t1 - t0).count() << " seconds\n";
    save_png("output.png", width, height, img);
}
