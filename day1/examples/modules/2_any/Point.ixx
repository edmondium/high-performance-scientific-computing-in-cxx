export module Point;

export struct Point {
    double X = 0, Y = 0;
    Point() = default;
    Point(const Point&) = default;
    Point(Point&&) = default;
    Point& operator=(const Point& p) = default;
    Point& operator=(Point&& p) = default;
    Point(double x, double y);
    Point& operator+=(const Point& p);
    Point& operator-=(const Point& p);
    Point operator+(const Point& p) const;
    Point operator-(const Point& p) const;
    double operator*(const Point& p) const;
    Point operator*(double f) const;
};

export auto operator*(double f, const Point& p) -> Point;
// export auto operator<<(std::ostream& os, const Point& p) -> std::ostream&;

Point::Point(double x, double y)
    : X{ x }
    , Y{ y }
{
}

Point& Point::operator+=(const Point& p)
{
    X += p.X;
    Y += p.Y;
    return *this;
}

Point& Point::operator-=(const Point& p)
{
    X -= p.X;
    Y -= p.Y;
    return *this;
}

Point Point::operator+(const Point& p) const
{
    return { X + p.X, Y + p.Y };
}

Point Point::operator-(const Point& p) const
{
    return { X - p.X, Y - p.Y };
}

double Point::operator*(const Point& p) const
{
    return (X * p.X + Y * p.Y);
}

Point Point::operator*(double f) const
{
    return { f * X, f * Y };
}

Point operator*(double f, const Point& p)
{
    return { f * p.X, f * p.Y };
}

/*
std::ostream& operator<<(std::ostream& os, const Point& p)
{
    os << "(" << p.X << ", " << p.Y << ")";
    return os;
}
*/
