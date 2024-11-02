class D {
    int nm;
    double d;

public:
    void val(double x) { d = x; }
    auto val() const -> double { return d; }
    auto name() const { return nm; }
    auto operator+(double x1) const -> double;
};
auto D::operator+(double x) const -> double
{
    return d + x * x;
}
