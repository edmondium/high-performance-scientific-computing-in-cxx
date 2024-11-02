#ifndef Circle_HH
#define Circle_HH
#include "Point.hh"
#include <string>

class Circle {
public:
    Circle() = default;
    Circle(double rad, const Point& p);
    Circle(const Circle& cir) = default;
    Circle(Circle&& cir) = default;
    Circle& operator=(const Circle& cir) = default;
    Circle& operator=(Circle&& cir) = default;
    std::string name() const { return "Circle"; }
    void rotate(double phi);
    void translate(Point p);
    double area() const;
    double perimeter() const;
    inline double circumference() const { return perimeter(); }

private:
    double r{ 1.0 };
    Point c{}; // Use default constructor of class Point to create c
};

#endif
