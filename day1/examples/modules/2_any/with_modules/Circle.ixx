export module Circle;
import <string>;
import <numbers>;
import Point;

using std::numbers::pi;

export class Circle {
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


Circle::Circle(double rad, const Point& p)
    : r{ rad }
    , c{ p }
{
}

double Circle::area() const
{
    return pi * r * r;
}

double Circle::perimeter() const
{
    return 2 * pi * r;
}

void Circle::rotate(double phi) { phi = 0; }

void Circle::translate(Point p)
{
    c += p;
}
