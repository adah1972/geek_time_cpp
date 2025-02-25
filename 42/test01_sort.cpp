#include <algorithm>       // std::ranges::sort
#include <functional>      // std::less
#include <iostream>        // std::cout
#include <string>          // std::string
#include <utility>         // std::pair
#include "output_range.h"  // operator<< for ranges

using namespace std;

int main()
{
    using MyPair = pair<int, string>;
    MyPair a[]{{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};
    ranges::sort(a, less{}, &MyPair::second);
    cout << a << '\n';
}
