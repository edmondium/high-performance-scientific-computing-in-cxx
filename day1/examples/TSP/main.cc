#include <random>
#include <span>
#include <vector>
#include <iostream>
#include <fstream>
#include <lyra/lyra.hpp>
import TSP;

auto main(int argc, char* argv[]) -> int
{
    bool randomstart{false}, showhelp{false};
    std::string file{};
    size_t nc{10UL};
    auto cmd = lyra::help(showhelp)
        | lyra::opt(file, "file")["-f"]["--file"]("Read city coordinates from file")
        | lyra::opt(randomstart)["-r"]["--random"]("Work with randomly generated city coordinates")
        | lyra::opt(nc, "ncities")["-n"]["--num-cities"]("How many cities to generate when using random start");

    auto result = cmd.parse( { argc, argv } );
    if ( !result ) {
        std::cerr << "Error in command line: " << result.message() << std::endl;
        std::cerr << cmd << "\n";
        exit(1);
    }
    if (showhelp) {
        std::cout << cmd << "\n";
        return 0;
    }

    std::vector<std::pair<double, double>> locs;
    if (randomstart) {
    double Lx = 100.;
    double Ly = 100.;
    locs.resize(nc);
    std::mt19937_64 eng{ std::random_device{}() };
    std::uniform_real_distribution<> uniform{};
    auto gen = [&](){ return uniform(eng); };
    for (auto& [x, y]: locs) {
        x = Lx * gen();
        y = Ly * gen();
    }
    } else {
        std::ifstream fin{file};
        if (not fin) {
            std::cerr << "Could not open file '" << file << "' for reading!\n";
            return 1;
        }
        double x, y;
        while (fin >> x >> y) { locs.emplace_back(x, y); }
    }
    std::cout << "City coordinates...\n";
    for (auto&& [x, y] : locs) std::cout << x << ", " << y << "\n";
    Cities cities(locs);
    Itinerary it(locs.size());
    auto mincost = cities.cost(it);
    auto best = it;
    std::cout << "Starting brute force search for " << locs.size() << " cities.\n";
    while (it.next()) {
        if (auto curcost = cities.cost(it); curcost < mincost) {
            best = it;
            mincost = curcost;
        }
    }
    std::cout << "Best route with cost = " << mincost << "\n"
              << best << "\n";
}

