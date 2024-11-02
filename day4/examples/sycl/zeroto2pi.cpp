#include <sycl.hpp>
#include <iostream>
#include <numbers>
#include <vector>
using namespace sycl;
using namespace std::numbers;

auto main() -> int {
    std::vector v(10'000'000, 0.0);
    queue q;
    {
        buffer v_buf{v};
        q.submit([&](handler& h){
            accessor v{v_buf, h};
            h.parallel_for(v.size(), [=](auto i){
                v[i] = 2 * pi * i / v.size();
            });
        });
    }
    std::cout << v[v.size() / 2] << '\n';
}
