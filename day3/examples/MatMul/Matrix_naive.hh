#include <cassert>
#include <vector>
#include <algorithm>
#include <random>

class matrix {
public:
    using value_type = double;
    auto nrows() const -> size_t { return nr; }
    auto ncols() const -> size_t { return nc; }
    auto operator()(size_t i, size_t j) const -> const auto& { return dat[i][j]; }
    auto operator()(size_t i, size_t j) -> auto& { return dat[i][j]; }
    matrix(size_t i, size_t j)
        : nr{ i }
        , nc{ j }
    {
        resize(nr, nc);
    }
    void resize(size_t i, size_t j)
    {
        nr = i;
        nc = j;
        dat.resize(nr);
        for (auto & d : dat) d.resize(nc);
    }
    matrix() = default;
    matrix(const matrix&) = delete;
    matrix(matrix&&) = default;
    auto operator=(matrix m) -> matrix&
    {
        swap(m);
        return *this;
    }
    void swap(matrix& m)
    {
        std::swap(nr, m.nr);
        std::swap(nc, m.nc);
        dat.swap(m.dat);
    }
    void random_fill()
    {
        static std::default_random_engine engine;
        static std::uniform_real_distribution<> dist;
        auto gen = [&]{ return dist(engine); };
        for (auto & d : dat) {
            std::generate(d.begin(), d.end(), gen);
        }
    }
    auto operator*(const matrix& m) const -> matrix
    {
        matrix ans(nr, m.nc);
        assert(nc == m.nr);
        for (auto i = 0ul; i < nr; ++i)
            for (auto j = 0ul; j<m.nc; ++j)
                for (auto k = 0ul; k <nc; ++k)
                    ans(i,j) += operator()(i,k) * m(k,j);
        return ans;
    }
    auto operator=(double x) -> matrix&
    {
        for (auto & d : dat) std::fill(d.begin(), d.end(), x);
        return *this;
    }
private:
    std::vector<std::vector<double>> dat;
    size_t nr{ 1 }, nc{ 1 };
};
