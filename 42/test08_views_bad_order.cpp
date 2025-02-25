#include <iostream>        // std::cout
#include <map>             // std::map
#include <ranges>          // std::views::*
#include <string>          // std::string
#include "output_range.h"  // operator<< for ranges

using namespace std;

int main()
{
    using MyPair = pair<int, string>;
    MyPair a[]{{1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}};
    int tf_count{};
    cout << (a | views::transform([&tf_count](const auto& pr) {
                 ++tf_count;
                 return pr.first;
             }) |
             views::filter([](int num) { return num % 2 == 0; }))
         << '\n';
    cout << tf_count << " transformations are made\n";
}
