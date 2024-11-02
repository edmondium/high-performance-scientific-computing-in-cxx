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

auto test1(int* arr1, int* arr2, unsigned N)
{
    std::cout << "Test 1\n";
    mycopy(arr1, arr1+5, arr2);
    std::cout << "Elements of A and B after copying A to B using mycopy...\n";
    for (unsigned i=0U; i < 5U; ++i) std::cout << arr1[i] << "\t" << arr2[i] << "\n";
    arr1[1] = 999;
    std::cout << "Elements of A and B after assigning 999 to the second element of A...\n";
    for (unsigned i=0U; i < 5U; ++i) std::cout << arr1[i] << "\t" << arr2[i] << "\n";
    std::cout << "\n\n";
}
auto test2(int* arr1, int* arr2, unsigned N)
{
    std::cout << "Test 2\n";
    arr2 = arr1;
    std::cout << "Elements of A and B after B = A ...\n";
    for (unsigned i=0U; i < 5U; ++i) std::cout << arr1[i] << "\t" << arr2[i] << "\n";
    arr1[1] = 999;
    std::cout << "Elements of A and B after assigning 999 to the second element of A...\n";
    for (unsigned i=0U; i < 5U; ++i) std::cout << arr1[i] << "\t" << arr2[i] << "\n";
    std::cout << "\n\n";
}

auto main() -> int
{
    {
        int A[]{2,3,4,5,6};
        int B[]{0,0,0,0,0};
        std::cout << "Elements of A and B after initialization...\n";
        for (unsigned i=0U; i < 5U; ++i) std::cout << A[i] << "\t" << B[i] << "\n";
        test1(A, B, 5);
    }
    std::cout << "***********************************\n";
    {
        int A[]{2,3,4,5,6};
        int B[]{0,0,0,0,0};
        std::cout << "Elements of A and B after initialization...\n";
        for (unsigned i=0U; i < 5U; ++i) std::cout << A[i] << "\t" << B[i] << "\n";
        test2(A, B, 5);
    }
}

