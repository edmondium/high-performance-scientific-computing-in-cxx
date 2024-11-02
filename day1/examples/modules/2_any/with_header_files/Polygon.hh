#ifndef Polygon_HH
#define Polygon_HH
#include "Point.hh"
#include <array>
#include <cmath>
#include <string>

template <unsigned int NV>
class Polygon {
    static_assert(NV > 2, "Can't have polygon with less than 3 sides");

public:
    Polygon() = default;
    Polygon(const Polygon&) = default;
    Polygon(Polygon&&) = default;
    Polygon& operator=(const Polygon& pg) = default;
    Polygon& operator=(Polygon&&) = default;
    constexpr auto n_vertexes() const { return NV; }
    std::string name() const { return "Polygon<" + std::to_string(NV) + ">"; }

    double perimeter() const
    {
        double ans = 0;
        for (size_t i = 1; i < vertex.size(); ++i) {
            ans += sqrt((vertex[i] - vertex[i - 1]) * (vertex[i] - vertex[i - 1]));
        }
        ans += sqrt((vertex.front() - vertex.back()) * (vertex.front() - vertex.back()));
        return ans;
    }
    void translate(Point p)
    {
        for (auto& pt : vertex)
            pt += p;
    }

    void rotate(double phi)
    {
        Point center;
        for (auto pt : vertex)
            center += pt;
        center = (1.0 / NV) * center;
        double ct = cos(phi), st = sin(phi);
        for (auto& pt : vertex) {
            auto rel = pt - center;
            pt = center + Point(ct * rel.X + st * rel.Y, -st * rel.X + ct * rel.Y);
        }
    }

protected:
    std::array<Point, NV> vertex;
};

#endif
