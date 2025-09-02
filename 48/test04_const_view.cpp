#include <iostream>        // std::cout
#include <ranges>          // std::ranges::cbegin/cend/range
#include <vector>          // std::vector
#include "output_range.h"  // operator<< for ranges

using namespace std;
namespace rg = ranges;

void outputTwoRangeItems(rg::range auto&& r)
{
    int count = 2;
    for (auto it = rg::cbegin(r); it != rg::cend(r); ++it) {
        if (count == 0) {
            break;
        }
        cout << *it << ' ';
#if !defined(__cpp_lib_ranges_as_const)
        *it += 2;  // Cannot compile since C++23
#endif
        --count;
    }
    cout << '\n';
#if !defined(__cpp_lib_ranges_as_const)
    cout << "Elements are modified even if cbegin and cend are used\n";
#endif
}

#if __cpp_lib_ranges_as_const >= 202207L
void outputTwoRangeItemsBetter(rg::range auto&& r)
{
    for (auto& item : r | views::as_const | views::take(2)) {
        cout << item << ' ';
        //item += 2;  // Cannot compile
    }
    cout << '\n';
}
#endif

int main()
{
    vector v{1, 2, 3, 4, 5};

    auto vr = v | views::reverse;
    outputTwoRangeItems(vr);

#if __cpp_lib_ranges_as_const >= 202207L
    auto vf = v | views::filter([](int n) { return n % 2 != 0; });
    outputTwoRangeItemsBetter(vf);
#else
    cout << v << '\n';
#endif
}
