#include <sycl.hpp>

auto main() -> int {
    auto N{1'000u};
    // Create a buffer of size N by N
    sycl::queue q;
    sycl::buffer<double, 2> bufA{sycl::range{N, N}};

    q.submit([&](sycl::handler& h){
        sycl::accessor accA{bufA, h, sycl::write_only, sycl::no_init};
        h.parallel_for(sycl::range{1000, 1000}, [=](sycl::item<2> it){
            // Use 2D idx to access 2D buffer
            accA[it.get_id()] = 0;
            // extract index components for traditional 2D access
            auto i = it[0];
            auto j = it[1];
            accA[i][j] = it.get_linear_id();
        });
    });
    {
        sycl::host_accessor accA{bufA};
        std::cout << "The linear index of [17, 511] is " << accA[17][511] << ".\n";
    }
}
