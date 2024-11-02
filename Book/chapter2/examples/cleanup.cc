#include <iostream>
#include <string>
#include <iomanip>

auto cleanup(const std::string& line) -> std::string
{
    return line;
}

auto main() -> int
{
    std::string line;
    do {
        std::cout << "Input: ";
        getline(std::cin, line);
        if (line.empty()) continue;
        auto cleanline = cleanup(line);
        std::cout << "Original input: " << std::quoted(line) << "\n";
        std::cout << "Cleaned up    : " << std::quoted(cleanline) << "\n";
    } while (not line.empty());
}

