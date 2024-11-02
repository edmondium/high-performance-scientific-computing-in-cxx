#pragma once
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

class FileAsLines {
public:
    using iterator = std::vector<std::string>::iterator;
    void read(std::filesystem::path nm)
    {
        std::ifstream fin { nm };
        std::string line;
        while (getline(fin, line))
            mylines.push_back(line);
    }
    FileAsLines(std::filesystem::path nm) { read(nm); }
    FileAsLines() = default;
    FileAsLines(const FileAsLines&) = default;
    FileAsLines(FileAsLines&&) = default;
    FileAsLines& operator=(const FileAsLines&) = default;
    FileAsLines& operator=(FileAsLines&&) = default;
    ~FileAsLines() = default;
    inline size_t size() const { return mylines.size(); }
    inline bool empty() const { return mylines.empty(); }
    inline const std::string& operator[](size_t i) const { return mylines[i]; }
    inline std::string& operator[](size_t i) { return mylines[i]; }
    inline const std::string& front() const { return mylines.front(); }
    inline std::string& front() { return mylines.front(); }
    inline const std::string& back() const { return mylines.back(); }
    inline std::string& back() { return mylines.back(); }
    inline decltype(auto) begin() { return mylines.begin(); }
    inline decltype(auto) end() { return mylines.end(); }
    inline decltype(auto) begin() const { return mylines.cbegin(); }
    inline decltype(auto) end() const { return mylines.cend(); }

private:
    std::vector<std::string> mylines;
};
std::ostream& operator<<(std::ostream& os, const FileAsLines& lines);

