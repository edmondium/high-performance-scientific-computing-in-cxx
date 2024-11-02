#pragma once
#include <iterator>
#include <type_traits>
#include <concepts>

template <std::integral T>
struct CountingIterator {
    using difference_type = std::make_signed_t<T>;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::random_access_iterator_tag;

    constexpr auto operator++() noexcept -> CountingIterator { return { ++val }; }
    constexpr auto operator++(int) noexcept -> CountingIterator { return { val++ }; }
    constexpr auto operator--() noexcept -> CountingIterator { return { --val }; }
    constexpr auto operator--(int) noexcept -> CountingIterator { return { val-- }; }
    constexpr auto operator+=(difference_type d)
    {
        val += d;
        return *this;
    }
    constexpr auto operator-=(difference_type d)
    {
        val -= d;
        return *this;
    }
    constexpr auto operator<(CountingIterator other) const noexcept -> bool { return val < other.val; }
    constexpr auto operator==(CountingIterator other) const noexcept -> bool { return val == other.val; }
    constexpr auto operator!=(CountingIterator other) const noexcept -> bool { return val != other.val; }
    constexpr auto operator>(CountingIterator other) const noexcept -> bool { return val > other.val; }
    constexpr auto operator<=(CountingIterator other) const noexcept -> bool { return val <= other.val; }
    constexpr auto operator>=(CountingIterator other) const noexcept -> bool { return val >= other.val; }
    constexpr auto operator*() const noexcept { return val; }
    constexpr auto operator*() noexcept -> auto& { return val; }
    constexpr auto operator->() noexcept -> auto* { return &val; }
    constexpr auto operator-(CountingIterator other) const noexcept -> difference_type { return val - other.val; }
    constexpr auto operator+(difference_type d) const noexcept -> CountingIterator { return { val + d }; }
    constexpr auto operator[](size_t d) const noexcept { return val + d; }
    T val {};
};
template <std::integral T>
struct Sequence {
    constexpr auto begin() const noexcept { return beg; }
    constexpr auto end() const noexcept { return nde; }
    using iterator = CountingIterator<T>;
    iterator beg{};
    iterator nde{std::numeric_limits<T>::max()};
    Sequence(T b, T e) noexcept : beg{b}, nde{e} {}
    explicit Sequence(T b) noexcept : beg{b} {}
};

template <std::integral T>
constexpr auto algo_counter(T t) noexcept -> CountingIterator<T> { return {t}; }

