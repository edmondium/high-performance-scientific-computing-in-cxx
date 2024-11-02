#include "range_output.hh"
#include <fstream>
#include <iostream>
#include <iterator>
#include <cxx20ranges>
#include <string>

// namespace sr = std::ranges;
// namespace sv = std::views;

int main(int argc, char* argv[])
{
    using namespace output;
    if (argc < 2) {
        std::cerr << "Usage:\n"
                  << argv[0] << " input_file_name\n";
        return 1;
    }
    auto gerund = [](std::string_view w) { return w.ends_with("ing"); };
    std::ifstream fin { argv[1] };
    auto in = sr::istream_view<std::string>(fin);
    std::cout << (in | sv::filter(gerund)) << "\n";
}
