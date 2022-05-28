#include <ios>       // std::boolalpha
#include <iostream>  // std::cout/endl

using namespace std;

template <typename... Args>
constexpr auto sum1l(Args... args)
{
    return (... + args);
}

template <typename... Args>
constexpr auto sum1r(Args... args)
{
    return (args + ...);
}

template <typename... Args>
constexpr auto sum2l(Args... args)
{
    return (0 + ... + args);
}

int main()
{
    cout << boolalpha;

    auto s1 = sum1l(1, 2, 3, 4, 5);
    cout << "sum1l(1, 2, 3, 4, 5) = " << s1 << endl;

    auto s2 = sum1l(1e16, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2);
    cout << "sum1l(1e16, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2) == 1e16: "
         << (s2 == 1e16) << endl;
    auto s3 = sum1r(1e16, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2);
    cout << "sum1r(1e16, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2, 0.2) == 1e16: "
         << (s3 == 1e16) << endl;

    auto s4 = sum2l(1, 2, 3, 4, 5);
    cout << "sum2l(1, 2, 3, 4, 5) = " << s4 << endl;

    // auto s5 = sum1l(); // won't compile
    auto s6 = sum2l();
    cout << "sum2l() = " << s6 << endl;
}
