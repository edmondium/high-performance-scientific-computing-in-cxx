#pragma once
#include <algorithm>
#include <iomanip>
#include <iosfwd>
#include <ranges>
#include <string>

namespace output {
template <class C>
concept RawArray = std::is_array_v<C>;
template <class C>
concept ArrayClass = requires(C c)
{
    { c[1ul] };
    { c.size() };
};

template <class C>
concept StringLike = std::convertible_to<C, std::string_view>;

namespace {
    //auto size(const Container auto& C) { return C.size(); }
    auto size(const RawArray auto& C) { return std::extent_v<std::remove_cvref_t<decltype(C)>>; }
}

template <class C>
concept ArrayLike = (not StringLike<C>)and(ArrayClass<C> or RawArray<C>);

template <class T>
void write_possibly_quoted(std::ostream& os, T&& t)
{
    if constexpr (StringLike<T>) {
        os << std::quoted(t);
    } else {
        os << t;
    }
}

std::ostream& operator<<(std::ostream& os, const ArrayLike auto& c)
{
    os << "[";
    auto sz = size(c);
    for (size_t i {}; i != sz; ++i) {
        write_possibly_quoted(os, c[i]);
        if (i + 1 < sz)
            os << ", ";
    }
    return os << "]";
}

template <class T>
requires(not StringLike<T> and std::ranges::range<T>)
    std::ostream&
    operator<<(std::ostream& os, T&& r)
{
    using namespace std::ranges;
    os << "[";
    //if (begin(r) != end(r))
    //    write_possibly_quoted(os, *begin(r));
    for (auto el : r) {
        write_possibly_quoted(os, el);
        os << ", ";
    }
    return os << "]";
}
template <class SepType>
class rprinter {
    std::ostream* strmptr = nullptr;
    SepType sep;

public:
    rprinter(SepType s)
        : sep { s }
    {
    }
    rprinter(const rprinter&) noexcept = default;
    std::ostream& stream() { return *strmptr; }
    void stream(std::ostream& os) { strmptr = &os; }
    const auto& separator() const noexcept { return sep; }
};
template <>
class rprinter<void> {
    std::ostream* strmptr = nullptr;

public:
    std::ostream& stream() { return *strmptr; }
    void stream(std::ostream& os) { strmptr = &os; }
};

template <class T>
rprinter<T> operator<<(std::ostream& os, rprinter<T> r)
{
    r.stream(os);
    return { r };
}
template <class T>
std::ostream& operator<<(rprinter<T> vp, std::ranges::range auto&& t)
{
    if constexpr (std::is_same_v<T, void>) {
        for (auto&& el : t)
            vp.stream() << el;
    } else {
        if (not std::ranges::empty(t)) {
            vp.stream() << *std::ranges::begin(t);
            std::ranges::for_each(t | std::views::drop(1), [&vp](auto&& el) {
                vp.stream() << vp.separator() << el;
            });
        }
    }
    return vp.stream();
}

inline rprinter<void> unseparated;
inline rprinter<const char*> comma_separated { ", " };

}
