#include <fstream>
#include <print>
#include <iterator>
#include <ranges>
#include <string>

namespace sr = std::ranges;
namespace sv = std::views;

auto main(int argc, char* argv[]) -> int
{
    if (argc < 2) {
        std::print(R"(Usage:
{} input_file_name
)", argv[0]);
        return 1;
    }
    auto gerund = [](std::string_view w) { return w.ends_with("ing"); };
    std::ifstream fin { argv[1] };
    auto in = sr::istream_view<std::string>(fin);
    std::print("{}\n", in | sv::filter(gerund));
}
