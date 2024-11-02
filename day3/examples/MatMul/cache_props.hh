#ifndef CACHE_PROPS_HH
#define CACHE_PROPS_HH

#ifndef CACHELINE_SIZE
#define CACHELINE_SIZE 32UL
#endif
#ifndef L1D_CACHE_SIZE
#define L1D_CACHE_SIZE 16384UL
#endif

template <typename D>
struct how_many {
    static constexpr size_t in_cacheline = CACHELINE_SIZE / sizeof(D);
    static constexpr size_t in_L1D_Cache = L1D_CACHE_SIZE / sizeof(D);
};
#endif
