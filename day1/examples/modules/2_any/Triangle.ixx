module;
#include <array>
#include <cmath>
export module Triangle;
import Polygon;
import Point;

export class Triangle : public Polygon<3U> {
public:
    using Polygon<3U>::Polygon;
    using Polygon<3U>::operator=;
    using Polygon<3U>::name;
    Triangle(Point p1, Point p2, Point p3);
    double area() const;
};
// not exported
inline double sqr(Point p) { return p * p; }

Triangle::Triangle(Point p1, Point p2, Point p3)
{
    vertex[0] = p1;
    vertex[1] = p2;
    vertex[2] = p3;
}

double Triangle::area() const
{
    double s = 0.5 * perimeter();
    double a = sqrt(sqr(vertex[0] - vertex[1]));
    double b = sqrt(sqr(vertex[0] - vertex[2]));
    double c = sqrt(sqr(vertex[1] - vertex[2]));
    return sqrt(s * (s - a) * (s - b) * (s - c));
}
