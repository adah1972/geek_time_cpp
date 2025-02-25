#include <iostream>        // std::cout
#include <numeric>         // std::iota
#include <ranges>          // std::views::iota
#include <vector>          // std::vector
#include "output_range.h"  // operator<< for ranges

using namespace std;

int main()
{
    vector<int> v(5);
    iota(v.begin(), v.end(), 1);
    cout << v << '\n';
    cout << views::iota(1, 6) << '\n';
    for (auto i : views::iota(6)) {
        if (i == 10) {
            break;
        }
        cout << i << ' ';
    }
    cout << '\n';
}
