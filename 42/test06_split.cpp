#include <charconv>        // std::from_chars
#include <iostream>        // std::cout
#include <ranges>          // std::ranges::to, std::views::split/transform
#include <string_view>     // std::string_view
#include <vector>          // std::vector
#include "output_range.h"  // operator<< for ranges

using namespace std;

int main()
{
#if __cpp_lib_ranges >= 202110L
    auto input = "192.168.1.0"sv;
    auto split_result = views::split(input, "."sv);
    for (auto item : split_result) {
        cout << string_view(item.data(), item.size()) << ' ';
    }
    cout << '\n';
#if __cpp_lib_ranges_to_container >= 202202L
    auto numerals = split_result | views::transform([](auto v) {
                        int i = 0;
                        std::from_chars(v.data(), v.data() + v.size(), i);
                        return i;
                    }) |
                    ranges::to<vector>();
    cout << numerals << '\n';
#endif
#else
    cout << "std::views::split is not yet properly supported in your "
            "environment\n";
#endif
}
