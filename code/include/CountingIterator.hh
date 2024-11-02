#pragma once
#include <concepts>
#include <compare>
#include <iterator>
#include <type_traits>

    template <std::integral T>
    struct CountingIterator {
        using difference_type = std::make_signed_t<T>;
        using value_type = T;
        using pointer = T*;
        using reference = T;
        using iterator_category = std::random_access_iterator_tag;

        constexpr auto operator++(int) noexcept -> CountingIterator { return { val++ }; }
        constexpr auto operator++() noexcept -> CountingIterator&
        {
            ++val;
            return *this;
        }
        constexpr auto operator--(int) noexcept -> CountingIterator { return { val-- }; }
        constexpr auto operator--() noexcept -> CountingIterator&
        {
            --val;
            return *this;
        }
        constexpr auto operator+=(difference_type d) -> CountingIterator&
        {
            val += d;
            return *this;
        }
        constexpr auto operator-=(difference_type d) -> CountingIterator&
        {
            val -= d;
            return *this;
        }
        constexpr auto operator<=>(const CountingIterator& other) const noexcept = default;
        constexpr auto operator*() const noexcept -> T { return val; }
        constexpr auto operator->() noexcept { return &val; }
        constexpr auto operator->() const noexcept { return &val; }
        constexpr auto operator[](size_t d) const noexcept -> T { return val + d; }
        T val {};
    };

    template <std::integral T>
    constexpr auto operator-(const CountingIterator<T>& one, const CountingIterator<T>& two) noexcept
        -> typename CountingIterator<T>::difference_type { return one.val - two.val; }

    template <std::integral T>
    constexpr auto operator+(const CountingIterator<T>& one,
                             typename CountingIterator<T>::difference_type d) noexcept
        -> CountingIterator<T> { return { one.val + d }; }
    template <std::integral T>
    constexpr auto operator+(typename CountingIterator<T>::difference_type d,
                             const CountingIterator<T>& one) noexcept
        -> CountingIterator<T> { return { one.val + d }; }
    template <std::integral T>
    constexpr auto operator-(const CountingIterator<T>& one,
                             typename CountingIterator<T>::difference_type d) noexcept
        -> CountingIterator<T> { return { one.val - d }; }
    template <std::integral T>
    constexpr auto operator-(typename CountingIterator<T>::difference_type d,
                             const CountingIterator<T>& one) noexcept
        -> CountingIterator<T> { return { d - one.val }; }

    template <std::integral T>
    CountingIterator(T) -> CountingIterator<T>;

    template <std::integral T>
    auto algo_counter(T i) -> CountingIterator<T> { return { i }; }
