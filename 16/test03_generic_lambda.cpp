#include <array>     // std::array
#include <iostream>  // std::cout/endl
#include <numeric>   // std::accumulate

using namespace std;

int main()
{
    array<int, 5> a{1, 2, 3, 4, 5};
    auto s = accumulate(a.begin(), a.end(), 0,
                        [](auto x, auto y) { return x + y; });
    cout << s << endl;
}
