#include <exception>
#include <print>

template <class Derived>
struct EnableCheckedAccess {
    auto at(std::size_t i) const
    {
        auto* d = static_cast<const Derived*>(this);
        if (i >= d->size())
            throw std::out_of_range(
                std::format(
                    "Index {} is out of range for container size {}",
                    i, d->size()));
        return (*d)[i];
    }
};

struct MyVec : EnableCheckedAccess<MyVec> {
    auto operator[](std::size_t i) const
    {
        return i * i;
    }
    auto size() const -> std::size_t { return 5UL; }
};

auto main(int argc, char* argv[]) -> int
{
    auto lim = argc > 1 ? std::stoul(argv[1]) : 5UL;
    MyVec v;
    try {
        for (auto i = 0UL; i < lim; ++i)
            std::print("Index = {}, value = {} \n", i, v.at(i));
    } catch (std::exception& err) {
        std::print("{}\n", err.what());
    }
}
