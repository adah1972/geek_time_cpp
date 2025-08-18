#include <climits>          // INT_MIN
#include <iostream>         // std::cout/endl
#include <string>           // std::string
#include <tl/expected.hpp>  // tl::expected/unexpected

using namespace std;

tl::expected<int, string> safe_divide(int i, int j)
{
    if (j == 0) {
        return tl::unexpected("divide by zero"s);
    }
    if (i == INT_MIN && j == -1) {
        return tl::unexpected("integer divide overflows"s);
    }
    if (i % j != 0) {
        return tl::unexpected("not integer division"s);
    }
    return i / j;
}

tl::expected<int, string> caller(int i, int j, int k)
{
    auto q = safe_divide(j, k);
    if (q) {
        return i + *q;
    } else {
        return q;
    }
}

template <typename T, typename E>
ostream& operator<<(ostream& os, const tl::expected<T, E>& exp)
{
    if (exp) {
        os << exp.value();
    } else {
        os << "unexpected: " << exp.error();
    }
    return os;
}

#define CHECK(expr)                                         \
    {                                                       \
        auto result = (expr);                               \
        cout << result;                                     \
        if (result == tl::unexpected("divide by zero"s)) {  \
            cout << ": Are you serious?";                   \
        } else if (result == 42) {                          \
            cout << ": Ha, I got you!";                     \
        }                                                   \
        cout << endl;                                       \
    }

int main()
{
    CHECK(caller(2, 1, 0));
    CHECK(caller(37, 20, 7));
    CHECK(caller(39, 21, 7));
}
