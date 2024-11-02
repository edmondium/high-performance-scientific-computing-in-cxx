#ifndef COUNTINGITERATOR_HH
#define COUNTINGITERATOR_HH
#include <iterator>
#include <type_traits>

template <typename T>
struct CountingIterator {
    static_assert(std::is_integral_v<T>, "Counting iterator template argument must be an integral type");
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
#endif
