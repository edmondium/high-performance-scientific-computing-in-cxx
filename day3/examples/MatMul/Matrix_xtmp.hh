#include <cassert>
#include <vector>
#include <algorithm>
#include "MatrixView.hh"
#include <random>

class matrix : public MatrixView<matrix> {
public:
    using value_type = double;
    auto nrows_() const -> size_t { return nr; }
    auto ncols_() const -> size_t { return nc; }
    auto row_(size_t i) const -> const auto* { return &dat[i * nc]; }
    auto row_(size_t i) -> auto* { return &dat[i * nc]; }

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
    matrix(const matrix&) = default;
    matrix(matrix&&) = default;
    using MatrixView<matrix>::operator=;
    auto operator=(matrix m) -> matrix&
    {
        swap(m);
        return *this;
    }

    struct matprod {
        const matrix& lhs;
        const matrix& rhs;
    };

    auto operator*(const matrix& m) const -> matprod
    {
        assert(nc == m.nr);
        return { *this, m };
    }

    auto operator=(const matprod& p) -> matrix&
    {
        operator=(0.);
        return operator+=(p);
    }

    auto operator+=(const matprod& p) -> matrix&
    {
        details::simple_ikj_mult(*this, p.lhs, p.rhs);
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
        std::generate(dat.begin(), dat.end(), gen);
    }
private:
    std::vector<double> dat;
    size_t nr{ 1 }, nc{ 1 };
};
