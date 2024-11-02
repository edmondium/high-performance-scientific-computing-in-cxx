import <iostream>;
import <array>;
import <vector>;
import <iterator>;
import <span>;
import saxpy;

auto main() -> int
{
    const std::array inp1 { 1., 2., 3., 4., 5. };
    const std::array inp2 { 9., 8., 7., 6., 5. };
    std::vector outp(inp1.size(), 0.);

    std::ostream_iterator<double> cout { std::cout, "\n" };
    saxpy(10., {inp1}, {inp2}, {outp});
    copy(outp.begin(), outp.end(), cout);
    std::cout << ":::::::::::::::::::::\n";
}
