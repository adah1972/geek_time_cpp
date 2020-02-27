#include <functional>   // std::ref
#include <iostream>     // std::cout/endl
#include <type_traits>  // std::decay_t
#include <utility>      // std::forward

using namespace std;

// Y combinator as presented by Yegor Derevenets in P0200R0
// <url:http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html>
template <class Fun>
class y_combinator_result {
    Fun fun_;
public:
    template <class T>
    explicit y_combinator_result(T&& fun)
        : fun_(std::forward<T>(fun))
    {
    }

    template <class... Args>
    decltype(auto) operator()(Args&&... args)
    {
        // y(f) = f(y(f))
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};

template <class Fun>
decltype(auto) y_combinator(Fun&& fun)
{
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

int main()
{
    auto almost_fact = [](auto f, int n) -> int {
        if (n == 0) {
            return 1;
        } else {
            return n * f(n - 1);
        }
    };
    auto fact = y_combinator(almost_fact);
    cout << fact(10) << endl;
}
