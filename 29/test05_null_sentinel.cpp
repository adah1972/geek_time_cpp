#if __cplusplus > 201703L
#include <algorithm>                      // std::ranges::for_each
#include <iterator>                       // std::input_iterator
namespace ranges = std::ranges;
using std::ranges::for_each;
using std::input_iterator;
#else
#include <experimental/ranges/algorithm>  // ranges::for_each
#include <experimental/ranges/iterator>   // ranges::input_iterator
namespace ranges = std::experimental::ranges;
using ranges::for_each;
using ranges::input_iterator;
#endif
#include <iostream>                       // std::cout/endl

struct null_sentinel {};

template <input_iterator I>
bool operator==(I i, null_sentinel)
{
    return *i == 0;
}

template <input_iterator I>
bool operator==(null_sentinel, I i)
{
    return *i == 0;
}

template <input_iterator I>
bool operator!=(I i, null_sentinel)
{
    return *i != 0;
}

template <input_iterator I>
bool operator!=(null_sentinel, I i)
{
    return *i != 0;
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cout << "Please provide an argument!" << std::endl;
        return 1;
    }
    for_each(argv[1], null_sentinel{}, [](char ch) { std::cout << ch; });
    std::cout << std::endl;
}
