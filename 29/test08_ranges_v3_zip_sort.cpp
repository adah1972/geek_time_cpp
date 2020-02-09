#include <iostream>
#include <string>
#include <vector>
#include <range/v3/all.hpp>

int main()
{
    std::vector<int> vd{1, 7, 3, 6, 5, 2, 4, 8};
    std::vector<std::string> vs{"one",  "seven", "three", "six",
                                "five", "two",   "four",  "eight"};
    auto v = ranges::views::zip(vd, vs);
    ranges::sort(v);
    for (auto i : vs) {
        std::cout << i << std::endl;
    }
}
