#include "CountingIterator.hh"
#include <algorithm>
#include <chrono>
#include <execution>
#include <iostream>
#include <ranges>
#include <span>
#include <vector>
#include <fstream>

namespace sr = std::ranges;
namespace sv = std::views;
void jx(std::span<double> out, std::span<const double> x)
{
    sr::for_each(sv::iota(1UL, x.size() - 1UL),
        [&](auto i) { out[i] += (x[i - 1] + x[i + 1]); });
    out[0] += (x[1] + x[x.size() - 1]);
    out[out.size() - 1] += (x[0] + x[x.size() - 2]);
}
void jy(std::span<double> out, std::span<const double> up, std::span<const double> down)
{
    sr::for_each(sv::iota(0UL, up.size()), [&](auto i) { out[i] += up[i] + down[i]; });
}

auto main() -> int
{
    const int rows = 500;
    const int cols = 2500;
    class Grid {
        std::vector<double> data;
        size_t nrows { 0UL }, ncols { 0UL };

    public:
        Grid(size_t nr, size_t nc)
            : data(nr * nc, 0.)
            , nrows { nr }
            , ncols { nc }
        {
        }
        void setseq()
        {
            sr::copy(sv::iota(0UL, nrows * ncols), begin(data));
        }
        void setzero()
        {
            sr::fill(data, 0.);
        }
        auto row(size_t i) const -> std::span<const double> { return { data.begin() + i * ncols, ncols }; }
        auto row(size_t i) -> std::span<double> { return { data.begin() + i * ncols, ncols }; }
        auto elements() const -> std::span<const double> { return { data.begin(), nrows * ncols }; }
        void set_row(size_t i, double vl) { sr::fill(row(i), vl); }
        void scale_row(size_t i, double fct)
        {
            sr::transform(row(i), row(i).begin(), [fct](auto x) { return fct * x; });
        }
    };
    Grid g1(rows, cols), g2(rows, cols);
    g1.setseq();
    auto tstart = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        std::for_each(std::execution::par, algo_counter(0), algo_counter(rows), [&](auto ir) {
            g2.set_row(ir, 0.);
            jx(g2.row(ir), g1.row(ir));
            auto rowup = (ir == 0 ? rows - 1 : ir - 1);
            auto rowdn = (ir == (rows - 1) ? 0 : ir + 1);
            jy(g2.row(ir), g1.row(rowup), g1.row(rowdn));
            g2.scale_row(ir, 0.25);
        });

        if (i % 100 == 0) {
            std::cout << "\n[" << i << "] ===============\n";
        }
        std::swap(g1, g2);
    }
    auto tend = std::chrono::high_resolution_clock::now();

    std::ofstream fout{"final.dat"};
    sr::for_each(g2.elements(), [&](const auto& p) {
        fout << p << " ";
    });
    fout.close();
    std::cout << "\n\nTotal simulation time = " << std::chrono::duration<double>(tend - tstart).count() << " seconds\n";
}
