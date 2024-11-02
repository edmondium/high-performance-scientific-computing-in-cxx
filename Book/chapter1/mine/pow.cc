#include <iostream>

auto main(int argc, char* argv[]) -> int
{
    auto x = std::stod(argv[1]);
    auto n = std::stoi(argv[2]);
    if (n >= 0) {
	    auto ans = 1.0;
	    while (n > 0) {
		    ans *= x;
		    --n;
	    }
    	    std::cout << ans << "\n";
    } else {
	    auto ans = 1.0;
	    while (n < 0) {
		    ans *= x;
		    ++n;
	    }
    	    std::cout << 1.0/ ans << "\n";
    }
}

