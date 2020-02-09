#if __cpp_concepts < 201811

#include <experimental/ranges/range>
namespace ranges =
  std::experimental::ranges;

#else

#include <ranges>
namespace ranges = std::ranges;

#endif

#include <iostream>
#include <vector>

std::vector<int> get_data()
{
  return std::vector{1, 2, 3};
}

int main()
{
  auto it = ranges::begin(get_data());
  int i = *it;  // BOOM
}
