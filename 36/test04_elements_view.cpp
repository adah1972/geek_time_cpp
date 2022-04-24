#include <iostream>        // std::cout/cerr/endl
#if __cplusplus > 201703L && __has_include(<ranges>)
#include <ranges>          // std::views
#endif

#if defined(__cpp_lib_ranges) && __cpp_lib_ranges >= 201911L

#include <map>             // std::map
#include <string>          // std::string
#include "output_range.h"  // operator<< for ranges

using namespace std;

int main()
{
    map<int, string> mp{{1, "one"}, {2, "two"}, {3, "three"}};
    auto vv = mp | views::values;
    auto vv1 = vv;
    cout << vv1 << endl;
}

#else

int main()
{
    std::cerr << "Ranges support is not detected\n";
    return 1;
}

#endif
