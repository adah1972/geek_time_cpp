#include <iostream>      // std::cout
#if __has_include(<version>)
#include <version>       // __cpp_lib_print
#endif

#define TEST_FORMAT_STD 1
#define TEST_FORMAT_FMT 2

#ifndef TEST_FORMAT
#if __cpp_lib_print >= 202207L
#define TEST_FORMAT TEST_FORMAT_STD
#elif __has_include(<fmt/format.h>)
#define TEST_FORMAT TEST_FORMAT_FMT
#endif
#endif

#if TEST_FORMAT == TEST_FORMAT_STD
#include <print>         // std::print
using std::print;
#elif TEST_FORMAT == TEST_FORMAT_FMT
#include <fmt/format.h>  // fmt::print
using fmt::print;
#endif

int main()
{
    auto msg = "你好，世界！";
#if TEST_FORMAT
    print("{}\n", msg);
#endif
    std::cout << msg << '\n';
}
