// examples/ignored.cc

template <class T>
auto getmem(unsigned long N, T init) -> T*
{
    T* ans = new T[N];
    for (auto i = 0UL; i < N; ++i) ans[i] = init;
    return ans;
}
auto main() -> int
{
    getmem(10'000'000, 0.); // how rude!
    getmem(10'000'000, 0.);
    getmem(10'000'000, 0.); 
}

