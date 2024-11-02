#pragma once
#ifndef CACHELINE_SIZE
#define CACHELINE_SIZE 32UL
#endif
#ifndef L1D_CACHE_SIZE
#define L1D_CACHE_SIZE 16384UL
#endif
#include <cstddef>

template <class D>
struct how_many {
    static constexpr size_t in_cacheline = CACHELINE_SIZE / sizeof(D);
    static constexpr size_t in_L1D_Cache = L1D_CACHE_SIZE / sizeof(D);
};
