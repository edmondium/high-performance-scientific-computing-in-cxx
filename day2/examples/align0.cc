#include <array>
#include <iostream>
#include <concepts>

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
template <class N> concept Number = std::floating_point<N> || std::integral<N>;
template <Number T>
struct alignas(vec_bytes<target_isa>) simd_t {
    static constexpr auto nelems = vec_bytes<target_isa> / sizeof(T);
    std::array<T, nelems> data;
    static_assert(vec_bytes<target_isa> % sizeof(T) == 0,
        "vector width must be an integral multiple of type size");
};

auto main() -> int
{
    std::cout << "Alignment for simd type (float) : " << alignof(simd_t<float>) << " with " 
              << simd_t<float>::nelems << " elements in vector\n";
    std::cout << "Alignment for simd type (double) : " << alignof(simd_t<double>) << " with " 
              << simd_t<double>::nelems << " elements in vector\n";
}
