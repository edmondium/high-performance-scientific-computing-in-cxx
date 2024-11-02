#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

auto main() -> int
{
    const std::vector inp1 { 1., 2., 3., 4., 5. };
    const std::vector inp2 { 9., 8., 7., 6., 5. };
    std::vector outp(inp1.size(), 0.);

    auto saxpy = []<class T, class T_in, class T_out>(T a, const T_in& x, const T_in& y, T_out& z) {
        std::transform(x.begin(), x.end(), y.begin(), z.begin(), 
                       [a](T X, T Y){ return a * X + Y; }); 
    };

    std::ostream_iterator<double> cout { std::cout, "\n" };
    saxpy(10., inp1, inp2, outp);
    copy(outp.begin(), outp.end(), cout);
    std::cout << ":::::::::::::::::::::\n";
}

