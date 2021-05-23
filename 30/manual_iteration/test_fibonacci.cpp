#if __cplusplus > 201703L
#include <ranges>                      // std::ranges::views
namespace views = std::ranges::views;
#else
#include <experimental/ranges/ranges>  // ranges::views
namespace views = std::experimental::ranges::views;
#endif
#include <iostream>                    // std::cout/endl
#include "fibonacci.hpp"               // fibonacci

using namespace std;

int main()
{
    using views::take;
    using views::take_while;
    for (auto i : fibonacci() | take(20)) {
        cout << i << endl;
    }
    for (auto i :
         fibonacci() | take_while([](uint64_t x) { return x < 10000; })) {
        cout << i << endl;
    }
}
