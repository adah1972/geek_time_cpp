#if __cplusplus > 201703L
#include <algorithm>                      // std::ranges::copy/sort
#include <iterator>                       // std::ostream_iterator
namespace ranges = std::ranges;
using std::ostream_iterator;
#else
#include <experimental/ranges/algorithm>  // ranges::copy/sort
#include <experimental/ranges/iterator>   // ranges::ostream_iterator
namespace ranges = std::experimental::ranges;
using ranges::ostream_iterator;
#endif
#include <iostream>                       // std::cout/endl

int main()
{
    int a[] = {1, 7, 3, 6, 5, 2, 4, 8};
    ranges::copy(a, ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    ranges::sort(a);
    ranges::copy(a, ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}
