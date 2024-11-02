module;
#include <cassert>
#ifdef USE_IMPORT_STD
import std;
#else
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#endif
export module TSP:Itinerary;
import :Cities;

using std::size_t;
export class Itinerary {
    std::vector<size_t> id, fxd;
public:
    Itinerary(size_t n) : id(n)
    {
        assert(n > 2UL);
        std::iota(id.begin(), id.end(), 0UL);
    }
    Itinerary() noexcept = default;
    ~Itinerary() noexcept = default;
    Itinerary(const Itinerary&) noexcept = default;
    Itinerary(Itinerary&&) noexcept = default;
    auto operator=(const Itinerary&) noexcept -> Itinerary& = default;
    auto operator=(Itinerary&&) noexcept -> Itinerary& = default;
    template <class RNG> requires
    requires (RNG rng) {
        { rng() } -> std::convertible_to<double>;
    }
    void update(RNG&& rng)
    {
        const auto i0 = 1UL + (id.size() - 1UL) * rng();
        const auto i1 = 1UL + (id.size() - 1UL) * rng();
        std::swap(id[i0], id[i1]);
    }
    void fix(std::span<const size_t> S)
    {
        fxd.clear();
	std::copy(S.begin(), S.end(), std::back_inserter(fxd));
	std::iota(id.begin(), id.end(), 0UL);
	std::partition(id.begin(), id.end(), [this](auto i) { return std::find(fxd.begin(), fxd.end(), i) != fxd.end(); });
	std::copy(fxd.begin(), fxd.end(), id.begin());
	std::sort(id.begin() + fxd.size(), id.end());
    }
    auto next() -> bool
    {
        return std::next_permutation(id.begin() + fxd.size(), id.end());
    }
    auto operator[](size_t i) const -> size_t { return id[i]; }
    auto begin() const noexcept { return id.begin(); }
    auto begin() noexcept { return id.begin(); }
    auto cbegin() noexcept { return id.cbegin(); }
    auto end() const noexcept { return id.end(); }
    auto end() noexcept { return id.end(); }
    auto cend() noexcept { return id.cend(); }
};

export auto operator<<(std::ostream& os, const Itinerary& it) -> std::ostream&
{
    os << "[";
    for (auto i : it) {
        os << i << ", ";
    }
    return os << "]";
}

