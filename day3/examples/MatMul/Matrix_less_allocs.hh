#include <cassert>
#include <vector>
#include <algorithm>

class matrix {
public:
    using value_type = double;
    auto nrows() const -> size_t { return nr; }
    auto ncols() const -> size_t { return nc; }
    auto operator()(size_t i, size_t j) const -> const auto& { return dat[nc * i + j]; }
    auto operator()(size_t i, size_t j) -> auto& { return dat[nc * i + j]; }
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
        dat.resize(nr * nc);
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
    template <class G>
    void fill(G& gen)
    {
        std::generate(dat.begin(), dat.end(), gen);
    }
    auto operator*(const matrix& m) const -> matrix
    {
        matrix ans(nr, m.nc);
        assert(nc == m.nr);
        for (auto i = 0ul; i < nr; ++i) {
            for (auto k = 0ul; k < nc; ++k) {
                auto aik = operator()(i,k);
                auto * crowi = &ans(i, 0ul);
                auto * browk = &m(k, 0ul);
                for (auto j = 0ul; j < m.nc; ++j) {
                    crowi[j] += aik * browk[j];
                }
            }
        }
        return ans;
    }
    auto operator=(double x) -> matrix&
    {
        std::fill(dat.begin(), dat.end(), x);
        return *this;
    }
private:
    std::vector<double> dat;
    size_t nr{ 1 }, nc{ 1 };
};
