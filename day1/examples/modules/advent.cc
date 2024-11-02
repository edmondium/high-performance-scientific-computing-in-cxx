/*
Calculates the date of the last advent in a given
year. Usage:

(i) advent           # calculate for current year
(ii) advent 2049     # for 2049
*/

import <chrono>;
import <iostream>;
auto current_year() -> std::chrono::year
{
    using namespace std::chrono;
    year_month_day date { floor<days>(system_clock::now()) };
    return date.year();
}

auto main(int argc, char* argv[]) -> int
{
    using namespace std::chrono;
    using namespace std::chrono_literals;
    using Date = year_month_day;

    year Y { argc == 1 ? current_year() : year {std::stoi(argv[1]) }};

    Date s4 { Y / December / Sunday[4] };
    Date s3 { Y / December / Sunday[3] };
    Date xmas { Y / December / 25d };
    Date lastadv { s4 >= xmas ? s3 : s4 };

    std::cout << "The last advent for the year "
              << static_cast<int>(Y) << " falls on "
              << static_cast<unsigned>(lastadv.day())
              << "'th of December.\n";
}
