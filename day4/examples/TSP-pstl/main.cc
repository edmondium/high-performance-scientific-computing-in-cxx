#include <fstream>
#include <iostream>
#include <lyra/lyra.hpp>
#include <random>
#include <span>
#include <vector>
#include <execution>
#include <chrono>
import TSP;

auto main(int argc, char* argv[]) -> int
{
    bool randomstart { false }, showhelp { false };
    std::string file {};
    size_t nc { 10UL };
    auto cmd = lyra::help(showhelp)
        | lyra::opt(file, "file")["-f"]["--file"]("Read city coordinates from file")
        | lyra::opt(randomstart)["-r"]["--random"]("Work with randomly generated city coordinates")
        | lyra::opt(nc, "ncities")["-n"]["--num-cities"]("How many cities to generate when using random start");

    auto result = cmd.parse({ argc, argv });
    if (!result) {
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
        std::mt19937_64 eng { std::random_device {}() };
        std::uniform_real_distribution<> uniform {};
        auto gen = [&]() { return uniform(eng); };
        for (auto& [x, y] : locs) {
            x = Lx * gen();
            y = Ly * gen();
        }
    } else {
        std::ifstream fin { file };
        if (not fin) {
            std::cerr << "Could not open file '" << file << "' for reading!\n";
            return 1;
        }
        double x, y;
        while (fin >> x >> y) {
            locs.emplace_back(x, y);
        }
    }
    std::cout << "City coordinates...\n";
    for (auto&& [x, y] : locs)
        std::cout << x << ", " << y << "\n";
    Cities cities(locs);
    Itinerary it(locs.size());
    std::vector<std::array<size_t, 4UL>> pathbeg;
    pathbeg.reserve(1000UL);
    for (auto i = 1UL; i < locs.size(); ++i) {
        for (auto j = 1UL; j < locs.size(); ++j) {
            if (j == i)
                continue;
            for (auto k = 1UL; k < locs.size(); ++k) {
                if (k == i or k == j)
                    continue;
                std::array<size_t, 4UL> tmp {};
                tmp[0] = 0UL;
                tmp[1] = i;
                tmp[2] = j;
                tmp[3] = k;
                pathbeg.push_back(tmp);
            }
        }
    }
    struct optimal_path_t {
        Itinerary path {};
        double cost {1.0e50};
        auto operator<(const optimal_path_t other) const noexcept { return cost < other.cost; }
    };
    std::cout << "Starting brute force search for " << locs.size() << " cities.\n";
    auto t0 = std::chrono::high_resolution_clock::now();
    auto [minpath, mincost] = std::transform_reduce(std::execution::par, pathbeg.begin(), pathbeg.end(), optimal_path_t {},
		    [](const optimal_path_t& o1, const optimal_path_t& o2) { return o1.cost <= o2.cost ? o1 : o2; },
        [&](auto&& fixedpart) {
            Itinerary it(locs.size());
            it.fix(fixedpart);
            auto mincost = cities.cost(it);
            auto best = it;
            while (it.next()) {
                if (auto curcost = cities.cost(it); curcost < mincost) {
                    best = it;
                    mincost = curcost;
                }
            }
            return optimal_path_t { best, mincost };
        });
    auto t1 = std::chrono::high_resolution_clock::now();
    std::cout << "Best route with cost = " << mincost << "\n"
              << minpath << "\n";
    std::cout << "Search took " << std::chrono::duration<double>(t1 - t0).count() << " seconds!\n";
}
