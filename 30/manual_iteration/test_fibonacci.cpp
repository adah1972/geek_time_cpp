#include <experimental/ranges/ranges>
#include <iostream>
#include "fibonacci.hpp"

using namespace std;

int main()
{
    using std::experimental::ranges::views::take;
    using std::experimental::ranges::views::take_while;
    for (auto i : fibonacci() | take(20)) {
        cout << i << endl;
    }
    for (auto i :
         fibonacci() | take_while([](uint64_t x) { return x < 10000; })) {
        cout << i << endl;
    }
}
