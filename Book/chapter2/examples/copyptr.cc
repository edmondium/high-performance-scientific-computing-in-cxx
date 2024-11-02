#include <iostream>

auto mycopy_n(unsigned howmany, int* source, int* destination)
    -> void
{
    for (unsigned i=0U; i<howmany; ++i) {
        destination[i] = source[i];
    }
}
auto mycopy(int* start, int* end,
            int* destination) -> void
{
    while (start != end) *destination++ = *start++;
}

auto main() -> int
{
    int A[]{2,3,4,5,6};
    int B[5];
    //mycopy_n(5, A, B);
    mycopy(A, A+5, B);
    for (auto b : B) std::cout << b << "\n";
}

