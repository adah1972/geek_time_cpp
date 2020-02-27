#include <experimental/ranges/ranges>  // ranges::views
#include <functional>                  // std::plus
#include <iostream>                    // std::cout/endl
#include <nvwa/functional.h>           // nvwa::reduce

using namespace std::experimental::ranges;

int main()
{
    int sum = nvwa::reduce(std::plus<int>(),
                           views::iota(1, 101) |
                           views::transform([](int x) { return x * x; }));

    std::cout << sum << std::endl;
}
