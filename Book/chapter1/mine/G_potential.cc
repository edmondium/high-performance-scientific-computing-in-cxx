#include <iostream>
#include <vector>

auto main() -> int
{
    const auto G = 6.674e-11;
    std::vector x{ 0., 1., 2., 3., 4., 5. };
    std::vector y{ 0., 1., 2., 3., 4., 5. };
    std::vector z{ 0., 1., 2., 3., 4., 5. };
    std::vector m{ 1.0e5, 1.0e5, 2.0e5, 1.0e5, 1.0e5, 1.0e5 };
    int size = x.size();
    
    auto total = 0.;
    // loop over index i from 0 till size.
    // loop over index j from i+1 till size
    // figure out where to put the end of the loops
    auto dx = x[i] - x[j];
    auto dy = y[i] - y[j];
    auto dz = z[i] - z[j];
    auto r2 = dx * dx + dy * dy + dz * dz;
    total = total + G * m[i] * m[j] / r2;
}
    std::cout << "Total gravitational potential energy = " << total << "\n";

}

