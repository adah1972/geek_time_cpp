#include <experimental/ranges/algorithm>
#include <experimental/ranges/iterator>
#include <iostream>

using namespace std::experimental::
  ranges;

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
    std::cout << "Please provide "
                 "an argument!"
              << std::endl;
    return 1;
  }
  for_each(argv[1], null_sentinel(),
           [](char ch) {
             std::cout << ch;
           });
  std::cout << std::endl;
}
