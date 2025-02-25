#include <algorithm>   // std::ranges::fold_left
#include <functional>  // std::plus
#include <iostream>    // std::cout
#include <ranges>      // std::views::iota/transform

using namespace std;

int main()
{
#if __cpp_lib_ranges_fold >= 202207L
    constexpr int sum = ranges::fold_left(
        views::iota(1, 101) | views::transform([](int x) { return x * x; }),
        0, plus<int>{});
    cout << sum << '\n';
#else
    cout << "std::ranges::fold_left is not yet supported in your "
            "environment\n";
#endif
}
