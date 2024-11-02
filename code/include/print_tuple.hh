#pragma once
#include <tuple>
#include <iostream>
#include <iomanip>

template <class ... Args>
std::ostream & operator<<(std::ostream & strm, const std::tuple<Args...> & t)
{
    using namespace std;
    auto print_one = [&strm](const auto & onearg) -> ostream & {
        using bare_type = remove_cv_t<remove_reference_t<decltype(onearg)>>;
        if constexpr (is_same_v<bare_type, string>)
            strm << quoted(onearg);
        else
            strm << onearg;
        return strm;
    };
    auto print_components = [&](const auto & ... args){
       ((print_one(args) << ", "), ...);
    };
    strm << "[";
    apply(print_components, t);
    return strm <<"]";
}


