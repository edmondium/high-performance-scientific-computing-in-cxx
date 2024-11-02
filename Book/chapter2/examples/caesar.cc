#include <algorithm>
#include <iostream>
#include <ranges>
#include <string>

auto caesar_shift(const std::string& inp, long shift) -> std::string
{
    using namespace std::string_literals;
    namespace sr = std::ranges;
    namespace sv = std::views;
    const auto alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"s;
    shift = shift % static_cast<long>(alphabet.size());
    // In the above, alphabet.size() is unsigned long. We want signed
    // numbers here, so we make an explicit cast. 
    // static_cast<ToType>(FromObj) explicitly converts an object of type
    // FromType (called FromObj here) to a new type ToType. Because of the
    // differences between signed and unsigned integers, the above
    // does not work correctly without an explicit cast.
    // Think why, and may be ask in the class!
    if (shift < 0)
        shift = alphabet.size() + shift;
    auto shifted = alphabet;
    sr::rotate(shifted, std::begin(shifted) + shift);
    // std::ranges::rotate(R, pos_in_R) takes a range R, and
    // an iterator in R, and rotates the elements in such a way
    // that the element at the original pos_in_R position becomes
    // the new first element.

    std::string ciphertext{ inp };
    return ciphertext;
}

auto main(int argc, char* argv[]) -> int
{
    if (argc != 2) {
        std::cerr << "Usage:\n" << argv[0] << " shift\n\n";
        return 1;
    }
    auto shift = std::stol(argv[1]);
    std::cout << "Enter your text below. To end input, enter an empty line.\n";
    std::string text, line;
    do {
        getline(std::cin, line);
        text += line;
    } while (not line.empty());
    std::cout << "Encrypted text ...\n";
    std::cout << caesar_shift(text, shift) << "\n\n";
}
