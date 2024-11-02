#include <exception>
#include <print>

struct EnableCheckedAccess {
    template <class Self>
    auto at(this Self&& self, std::size_t i) 
    {
        if (i >= self.size())
            throw std::out_of_range(
                std::format(
                    "Index {} is out of range for container size {}",
                    i, self.size()));
        return self[i];
    }
};

struct MyVec : EnableCheckedAccess {
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
