#if __cplusplus > 201703L
#include <ranges>                      // std::ranges::views
namespace ranges = std::ranges;
#else
#include <experimental/ranges/ranges>  // ranges::views
namespace ranges = std::experimental::ranges;
#endif
#include <functional>                  // std::plus
#include <iostream>                    // std::cout/endl
#include <nvwa/functional.h>           // nvwa::reduce

int main()
{
    namespace views = ranges::views;
    int sum = nvwa::reduce(std::plus<int>(),
                           views::iota(1, 101) |
                           views::transform([](int x) { return x * x; }));

    std::cout << sum << std::endl;
}
