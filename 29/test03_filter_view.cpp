#include <experimental/ranges/algorithm>  // ranges::copy/sort
#include <experimental/ranges/iterator>   // ranges::ostream_iterator
#include <experimental/ranges/ranges>     // ranges::filter_view
#include <iostream>                       // std::cout/endl

int main()
{
    using namespace std::experimental::ranges;
    int a[] = {1, 7, 3, 6, 5, 2, 4, 8};
    copy(a, ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    auto r = filter_view(a, [](int i) { return i % 2 == 0; });
    copy(r, ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
}
