[[gnu::noinline]] auto foo(double x) -> double 
{
    return x + 1.0;
}

[[gnu::noinline]] auto bar(const double& x) -> double
{
    return x + 1.0;
}

auto foobar() -> double
{
    double x = 1.0;
    double y = 2.0;
    return foo(x) + bar(y);
}
