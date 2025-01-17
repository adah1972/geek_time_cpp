#include <array>     // std::array
#include <iostream>  // std::cout
#include <list>      // std::list
#include <vector>    // std::vector

#if __cplusplus > 201703L && __has_include(<span>) && !defined(USE_GSL)
#include <span>      // std::span
using std::span;
#else
#include <gsl/span>  // gsl::span
using gsl::span;
#endif

void print(span<const int> sp)
{
    for (int n : sp) {
        std::cout << n << ' ';
    }
    std::cout << '\n';
}

void increase(span<int> sp, int value = 1)
{
    for (int& n : sp) {
        n += value;
    }
}

int main()
{
    std::array a{1, 2, 3, 4, 5};
    int b[]{1, 2, 3, 4, 5};
    std::vector v{1, 2, 3, 4, 5};
    std::list lst{1, 2, 3, 4, 5};

    print(a);
    print(b);
    print(v);
    // print(lst); // Cannot compile
    std::cout << '\n';

    increase(a);
    increase(b, 2);
    print(a);
    print(b);
    print(v);

    span sp{a};
    sp[5] = 0;  // Crashes when using gsl::span
}
