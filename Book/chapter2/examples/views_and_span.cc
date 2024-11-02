// examples/views_and_span.cc
#include <iostream>
#include <span>
#include <ranges>
#include <algorithm>
#include <string>
#include <iomanip>

auto main(int argc, char * argv[]) -> int
{
    std::span args(argv, argc);
    auto str = [](auto inp) -> std::string_view { return inp; };
    if (argc < 2) {
        std::cout << "Usage:\n"
                  << argv[0] << " some strings in the command line\n";
        return 1;
    }
    namespace sr = std::ranges;
    namespace sv = std::views;
    auto [first, last] = sr::minmax( args | sv::drop(1) | sv::transform(str) );

    std::cout << "Alphabetically first and last strings in your input are " 
              << std::quoted(first) << " and " << std::quoted(last) << "\n";
}

