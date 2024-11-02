module;
#include <cassert>
// This can not come from "import std;", because
// assert() is a macro, and macros are not exported
// in modules. For assert, we have to continue with
// the header. 
#ifdef USE_IMPORT_STD
import std;
#else
#include <vector>
#include <cmath>
#include <span>
#include <numeric>
#include <algorithm>
#endif
export module TSP:Cities;

using std::size_t;

export class Cities {
public:
    Cities() = default;
    Cities(const Cities&) noexcept = default;
    Cities(Cities&&) noexcept = default;
    auto operator=(const Cities&) noexcept -> Cities& = default;
    auto operator=(Cities&&) noexcept -> Cities& = default;
    Cities(std::span<std::pair<double, double>> lst)
    {
        pos.resize(lst.size());
        std::copy(lst.begin(), lst.end(), pos.begin());
        indexes.resize(lst.size());
        std::iota(indexes.begin(), indexes.end(), 0UL);
    }
    auto size() const noexcept -> size_t { return indexes.size(); }
    auto dist(size_t i, size_t j) const -> double
    {
        auto&& [lx, ly] = pos[i];
        auto&& [rx, ry] = pos[j];
        return std::sqrt((rx - lx) * (rx - lx) + (ry - ly) * (ry - ly));
    }
    auto cost(std::span<size_t> itinerary) const -> double
    {
        assert((itinerary.size() > 2UL) and
               itinerary.front() == 0UL and 
               std::is_permutation(itinerary.begin() + 1UL, itinerary.end(),
                                   indexes.begin() + 1UL));
        auto tot = 0.;
        auto iprev = 0UL;
        for (auto i : itinerary) {
            tot += dist(i, iprev);
            iprev = i;
        }
        return tot;
    }

private:
    std::vector<std::pair<double, double>> pos;
    std::vector<size_t> indexes;
};

