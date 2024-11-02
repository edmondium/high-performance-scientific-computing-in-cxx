#include <array>
#include <iostream>
#include <type_traits>
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

template <class T> /* requires std::is_arithmetic_v<T> : here, we leave this out deliberately to make it compatible with C++14 */
struct alignas(vec_bytes<target_isa>) simd_t {
    static_assert(vec_bytes<target_isa> % sizeof(T) == 0, "vector width must be an integral multiple of type size");
    static constexpr auto nelems = vec_bytes<target_isa> / sizeof(T);
    std::array<T, nelems> data;
};

auto alignof_address(void* ptr) -> size_t
{
    auto n = size_t(ptr);
    return ((-n) & n);
}

auto main() -> int
{
    std::cout << "Alignment for simd type (float) : " 
        << alignof(simd_t<float>) << " with " 
        << simd_t<float>::nelems << " elements in vector\n";

    std::cout << "Alignment for simd type (double) : " 
        << alignof(simd_t<double>) << " with " 
        << simd_t<double>::nelems << " elements in vector\n";

    auto* harr = new simd_t<double>[40];
    std::cout << "Alignment for heap allocated array of simd_t<double> : " 
        << alignof_address(harr) << "\n";

    std::vector<simd_t<double>> v(400);
    std::cout << "Alignment of data section of std::vector<simd_t<double>> on the heap = " 
        << alignof_address(v.data()) << "\n";
}

