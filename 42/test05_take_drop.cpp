#include <iostream>        // std::cout
#include <ranges>          // std::views::iota/take/drop/...
#include "output_range.h"  // operator<< for ranges

using namespace std;

int main()
{
#if __cpp_lib_ranges >= 201911L &&                                         \
    !(defined(__clang__) && _LIBCPP_VERSION < 160000)
    auto seq = views::iota(0, 10);
    cout << (seq | views::take(5)) << '\n';
    cout << (seq | views::take_while([&](int i) { return i < 5; })) << '\n';
    cout << (seq | views::drop(5)) << '\n';
    cout << (seq | views::drop_while([&](int i) { return i < 5; })) << '\n';
#else
    cout << "Some views are not supported in your environment\n";
#endif
}
