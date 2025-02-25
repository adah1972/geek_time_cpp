#include <iostream>        // std::cout
#include <ranges>          // std::ranges::to, std::views::join/transform
#include <string>          // std::string/to_string
#include <vector>          // std::vector
#include "output_range.h"  // operator<< for ranges

using namespace std;

int main()
{
#if __cpp_lib_ranges_to_container >= 202202L
    vector input{192, 168, 1, 0};
    auto s = input | views::transform([first = true](int x) mutable {
                 if (first) {
                     first = false;
                     return to_string(x);
                 } else {
                     string result{"."};
                     result += to_string(x);
                     return result;
                 }
             }) |
             views::join |
             ranges::to<string>();
    cout << s << '\n';
#else
    cout << "std::ranges::to and std::views::join are required\n";
#endif
}
