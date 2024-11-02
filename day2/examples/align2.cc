#include <array>
#include <iostream>
#include <memory>
#include <new>
#include <concepts>
#include <vector>

enum class ISA { SSE,
    AVX,
    AVX512,
    MIC };
template <ISA isa> constexpr auto vec_bytes = 8UL;
template <> constexpr auto vec_bytes<ISA::SSE> = 16UL;
template <> constexpr auto vec_bytes<ISA::AVX> = 32UL;
template <> constexpr auto vec_bytes<ISA::AVX512> = 64UL;
template <> constexpr auto vec_bytes<ISA::MIC> = 64UL;

constexpr ISA target_isa = ISA::AVX512;

template <class N> concept Number = std::floating_point<N>
                                || std::integral<N>;

template <Number T>
struct alignas(vec_bytes<target_isa>) simd_t {
    static constexpr auto nelems = vec_bytes<target_isa> / sizeof(T);
    std::array<T, nelems> data;
    static_assert(vec_bytes<target_isa> % sizeof(T) == 0, "vector width must be an integral multiple of type size");
};

auto alignof_address(void* ptr) -> size_t
{
    size_t numeric = size_t(ptr);
    size_t al = 1;
    while ((numeric & 1) == 0) {
        al <<= 1;
        numeric >>= 1;
    }
    return al;
}

auto main() -> int
{
    std::cout << "Alignment for simd type (float) : " 
        << alignof(simd_t<float>) << " with " 
        << simd_t<float>::nelems << " elements in vector\n";

    std::cout << "Alignment for simd type (double) : " 
        << alignof(simd_t<double>) << " with " 
        << simd_t<double>::nelems << " elements in vector\n";

    std::unique_ptr<simd_t<double>[]> harr { new simd_t<double>[40] };
    std::cout << "Alignment for heap allocated array of simd_t<double> : " 
        << alignof_address(harr.get()) << "\n";
 
    std::vector<double> v(400, 0.);
    std::cout << "Alignment of data section of std::vector on the heap = " 
        << alignof_address(v.data()) << "\n";

    auto darr = std::make_unique<double[]>(40);
    std::cout << "Alignment for heap allocated array of ordinary double : " 
        << alignof_address(darr.get()) << "\n";

    darr.reset(new double[40]);
    std::cout << "Alignment for heap allocated array of ordinary double : " 
        << alignof_address(darr.get()) << "\n";

    std::cout << "Dynamic allocation using C++17 overaligned new ... \n";
    darr.reset(new (static_cast<std::align_val_t>(64UL)) double[40]);
    std::cout << "Alignment for heap allocated array of ordinary double (specified: 64) : " 
        << alignof_address(darr.get()) 
        << "\n^^^ This here was done by specifying alignment to the 'new' operator directly\n";

    std::vector<simd_t<double>> w(4);
    std::cout << "Alignment of data section of std::vector for simd_t<double> = " 
        << alignof_address(w.data()) << "\n";
}

