#include <iostream>        // std::cout
#include <version>         // __cpp_lib_three_way_comparison

#if __cpp_lib_three_way_comparison >= 201907L || _LIBCPP_VERSION >= 160000

#include <set>             // std::set
#include <math.h>          // NAN
#include "employee.h"      // Employee
#include "output_range.h"  // operator<< for ranges

int main()
{
#if !(defined(__GNUC__) && !defined(__clang__) && __GNUC__ < 12) &&        \
    !defined(_MSC_VER)
    // MSVC does not handle NAN comparisons well even with /fp:strict
    static_assert(!(NAN < 1));
    static_assert(!(1 < NAN));
    static_assert(!(NAN < 1));
    static_assert(!(1 < NAN));
    static_assert(!(1 == NAN));
    static_assert(!(NAN == NAN));
    static_assert(1 != NAN);
    static_assert(NAN != NAN);
#endif

    std::set<Employee> s;
    s.emplace("1", "Liza", 1998, 4080);
    s.emplace("2", "John", 2001, 3090);

    std::cout << s << '\n';
}

#else

int main()
{
    std::cout << "Three-way comparison is not supported in your environment\n";
}

#endif
