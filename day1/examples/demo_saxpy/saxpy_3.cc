#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

auto main() -> int
{
    const std::vector inp1 { 1., 2., 3., 4., 5. };
    const std::vector inp2 { 9., 8., 7., 6., 5. };
    std::vector outp(inp1.size(), 0.);

    auto saxpy = []<class T_in, class T_out>(typename std::remove_cvref_t<T_in>::value_type a, 
                                             T_in&& x, T_in&& y, T_out& z) {
        using in_element_type = typename std::remove_cvref_t<T_in>::value_type;
        using out_element_type = typename std::remove_cvref_t<T_out>::value_type;
        static_assert(std::is_same_v<in_element_type, out_element_type>, "Input and output element types must match!");
        std::transform(x.begin(), x.end(), y.begin(), z.begin(), 
                       [a](in_element_type X, in_element_type Y){ return a * X + Y; }); 
    };

    std::ostream_iterator<double> cout { std::cout, "\n" };
    saxpy(10., inp1, inp2, outp);
    copy(outp.begin(), outp.end(), cout);
    std::cout << ":::::::::::::::::::::\n";
}

