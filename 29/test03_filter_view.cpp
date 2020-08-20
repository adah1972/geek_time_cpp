#if __cplusplus > 201703L
#include <algorithm>                      // std::ranges::copy
#include <iterator>                       // std::ostream_iterator
#include <ranges>                         // std::ranges::filter_view
namespace ranges = std::ranges;
using std::ostream_iterator;
#else
#include <experimental/ranges/algorithm>  // ranges::copy
#include <experimental/ranges/iterator>   // ranges::ostream_iterator
#include <experimental/ranges/ranges>     // ranges::filter_view
namespace ranges = std::experimental::ranges;
using ranges::ostream_iterator;
#endif
#include <iostream>                       // std::cout/endl

int main()
{
    int a[] = {1, 7, 3, 6, 5, 2, 4, 8};
    ranges::copy(a, ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    auto r = ranges::filter_view(a, [](int i) { return i % 2 == 0; });
    ranges::copy(r, ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}
