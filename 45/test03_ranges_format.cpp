#include <iostream>      // std::cout
#if __has_include(<version>)
#include <version>       // __cpp_lib_format_ranges/__cpp_lib_ranges
#endif

#define TEST_FORMAT_STD 1
#define TEST_FORMAT_FMT 2

#ifndef TEST_FORMAT
#if __cpp_lib_format_ranges >= 202207L
#define TEST_FORMAT TEST_FORMAT_STD
#elif __has_include(<fmt/format.h>) && __cpp_lib_ranges >= 201911L
#define TEST_FORMAT TEST_FORMAT_FMT
#endif
#endif

#if TEST_FORMAT == TEST_FORMAT_STD
#include <format>        // std::format
using std::format;
#elif TEST_FORMAT == TEST_FORMAT_FMT
#include <fmt/ranges.h>  // fmt support for ranges
using fmt::format;
#endif

#if TEST_FORMAT

#include <map>           // std::map
#include <ranges>        // std::views::keys
#include <string>        // std::string
#include <utility>       // std::pair
#include <vector>        // std::vector

using std::cout;
using std::map;
using std::pair;
using std::string;
using std::vector;
namespace views = std::views;

int main()
{
    map<int, string> mp{{1, "one"}, {2, "two"}, {3, "three"}};
    vector<pair<int, string>> v(mp.begin(), mp.end());
    auto keys = views::keys(mp);

    // ADL can find the wrong version with unqualified lookup
    cout << ::format("{}\n", mp);
    cout << ::format("{}\n", v);
#if TEST_FORMAT == TEST_FORMAT_STD
    cout << ::format("{:^37}\n", keys);
#else
    cout << ::format("{}\n", keys);
#endif
}

#else

int main()
{
    std::cout << "Range formatting is not supported in your environment\n";
}

#endif
