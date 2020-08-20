#if __cplusplus > 201703L
#include <ranges>                     // std::ranges::begin
namespace ranges = std::ranges;
#else
#include <experimental/ranges/range>  // ranges::begin
namespace ranges = std::experimental::ranges;
#endif
#include <vector>                     // std::vector

std::vector<int> get_data()
{
    return std::vector{1, 2, 3};
}

int main()
{
    auto it = ranges::begin(get_data());
    int i = *it;  // BOOM
}
