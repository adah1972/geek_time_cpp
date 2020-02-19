#include <iostream>

using namespace std;

template <typename T>
constexpr auto sum(T x)
{
    return x;
}

template <typename T1, typename T2, typename... Targ>
constexpr auto sum(T1 x, T2 y, Targ... args)
{
    return sum(x + y, args...);
}

int main()
{
    short x = 12345;
    auto result = sum(1, 2, 3.5, x);
    cout << result << endl;
}
