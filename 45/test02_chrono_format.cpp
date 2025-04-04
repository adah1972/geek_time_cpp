#include <chrono>        // std::chrono::*
#include <iostream>      // std::cout
#if __has_include(<version>)
#include <version>       // __cpp_lib_chrono
#endif

#define TEST_FORMAT_STD 1
#define TEST_FORMAT_FMT 2

#ifndef TEST_FORMAT
#if __cplusplus >= 202002L
#if __cpp_lib_chrono >= 201611L && __has_include(<format>)
#define TEST_FORMAT TEST_FORMAT_STD
#elif __has_include(<fmt/chrono.h>)
#define TEST_FORMAT TEST_FORMAT_FMT
#endif
#endif
#endif

#if TEST_FORMAT == TEST_FORMAT_STD
#include <format>        // std::format
using std::format;
#elif TEST_FORMAT == TEST_FORMAT_FMT
#include <fmt/chrono.h>  // fmt support for chrono types
using fmt::format;
#endif

#if TEST_FORMAT

using namespace std::chrono;
using std::cout;

int main()
{
    auto dt = 2025y/3/18;
#if TEST_FORMAT == TEST_FORMAT_STD
    cout << dt << '\n';
    // {fmt} does not support the formatting of year_month_day
    cout << ::format("{:%F}\n", dt);
#endif

    auto now = floor<milliseconds>(system_clock::now());
#if TEST_FORMAT == TEST_FORMAT_STD
    cout << now << '\n';
#endif
    cout << ::format("{:%F}\n", now);
    cout << ::format("{:%F %T}\n", now);
    cout << ::format("{:%F %T %Z}\n", now);
}

#else

int main()
{
    std::cout << "Chrono formatting is not supported in your environment\n";
}

#endif
