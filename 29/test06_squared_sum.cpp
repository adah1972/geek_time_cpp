#include <experimental/ranges/range>
#include <iostream>
#include <nvwa/functional.h>

using namespace std::experimental::ranges;

int main()
{
    int sum = nvwa::reduce(std::plus<int>(),
                           views::iota(1, 101) |
                           views::transform([](int x) { return x * x; }));

    std::cout << sum << std::endl;
}
