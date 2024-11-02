#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

auto main() -> int
{
    const std::vector inp1 { 1., 2., 3., 4., 5. };
    const std::vector inp2 { 9., 8., 7., 6., 5. };
    std::vector outp(inp1.size(), 0.);

    auto saxpy = [](double a, const std::vector<double>& x, const std::vector<double>& y,
                    std::vector<double>&z) {
        std::transform(x.begin(), x.end(), y.begin(), z.begin(), 
                       [a](double X, double Y){ return a * X + Y; }); 
    };

    std::ostream_iterator<double> cout { std::cout, "\n" };
    saxpy(10., inp1, inp2, outp);
    copy(outp.begin(), outp.end(), cout);
    std::cout << ":::::::::::::::::::::\n";
}

