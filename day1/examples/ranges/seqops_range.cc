#include "range_output.hh"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>
#include <vector>

int main()
{
    using namespace std;
    namespace sr = std::ranges;
    using namespace output;
    vector v { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    cout << "Vector v = (after initialization): " << v << "\n";
    if (sr::is_sorted(v))
        cout << "The sequence is sorted in the increasing order.\n";
    else
        cout << "The sequence is not sorted in the increasing order.\n";

    sr::reverse(v);
    cout << "After std::ranges::reverse: " << v << "\n";

    sr::rotate(v, v.begin() + 3);
    cout << "After std::rotate by 3" << v << "\n";

    sr::sort(v);
    cout << "After std::ranges::sort" << v << "\n";

    vector<int> w { 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 }, x, y, z;
    cout << "Vector w = " << w << "\n";

    vector<int> m;
    sr::merge(v, w, std::back_inserter(m));
    cout << "ranges::merge of v and w gives ... : " << m << "\n";

    sr::set_union(v, w, back_inserter(x));
    cout << "Union of v and w : " << x << "\n";

    sr::set_intersection(w, v, back_inserter(y));
    cout << "Intersection of w and v : " << y << "\n";

    sr::set_symmetric_difference(v, w, back_inserter(z));
    cout << "Symmetric difference of v and w : " << z << "\n";

    if (sr::is_permutation(z, v)) {
        cout << "The above sequence is a permutation of the first sequence printed.\n";
    } else {
        cout << "The above sequence is not a permutation of the first sequence printed.\n";
    }
}
