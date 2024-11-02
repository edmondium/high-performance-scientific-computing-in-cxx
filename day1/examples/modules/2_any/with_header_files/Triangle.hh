#include "Polygon.hh"

class Triangle : public Polygon<3> {
public:
    using Polygon<3>::Polygon;
    using Polygon<3>::operator=;
    Triangle(Point p1, Point p2, Point p3);
    double area() const;
};
