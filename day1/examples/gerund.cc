#include "range_output.hh"
#include <fstream>
#include <iostream>
#include <iterator>
#include <ranges>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    using namespace output;
    namespace sr = std::ranges;
    namespace sv = std::views;
    if (argc < 2) {
        std::cerr << "Usage:\n"
                  << argv[0] << " input_file_name\n";
        return 1;
    }
    std::ifstream fin { argv[1] };
    auto in = sr::istream_view<std::string>(fin);
    std::cout << (in | sv::filter([](auto&& w) { return w.ends_with("ing"); })) << "\n";
}
