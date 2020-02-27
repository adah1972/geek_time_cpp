#include <iostream>           // std::cout/endl
#include <numeric>            // std::accumulate
#include <utility>            // std::forward
#include <vector>             // std::vector
#include <nvwa/functional.h>  // nvwa::fmap

using namespace std;
using nvwa::fmap;

template <typename F>
auto compose(F f)
{
    return [f](auto&&... x) { return f(forward<decltype(x)>(x)...); };
}

template <typename F,
          typename... Args>
auto compose(F f, Args... other)
{
    return [f, other...](auto&&... x) {
        return f(compose(other...)(forward<decltype(x)>(x)...));
    };
}

int main()
{
    auto square_list = [](auto&& container) {
        return fmap([](int x) { return x * x; }, container);
    };
    auto sum_list = [](auto&& container) {
        return accumulate(container.begin(), container.end(), 0);
    };
    auto squared_sum = compose(sum_list, square_list);
    vector v{1, 2, 3, 4, 5};
    cout << squared_sum(v) << endl;
}
