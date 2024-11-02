auto sum(unsigned long n)
{
    decltype(n) s{};
    for (auto i = 0UL; i < n; ++i) {
        s += i;
    }
    return s;
}

