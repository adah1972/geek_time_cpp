#include <iostream>      // std::cout
#include <stdio.h>       // stdout
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
#include <format>        // std::format
#include <print>         // std::print/println
using std::format;
using std::print;
using std::println;
#elif TEST_FORMAT == TEST_FORMAT_FMT
#include <fmt/format.h>  // fmt::format/print/println
#if FMT_VERSION >= 100000
#include <fmt/ostream.h> // fmt support for ostream
using fmt::format;
using fmt::print;
using fmt::println;
#else
// Older {fmt} versions do not support println
#undef TEST_FORMAT
#endif
#endif

using std::cout;

int main()
{
    cout << "The answer is " << 42 << ".\n";
#if TEST_FORMAT
    cout << format("The answer is {}.\n", 42);
    print("The answer is {}.\n", 42);
    println("The answer is {}.", 42);
    print(stdout, "The answer is {}.\n", 42);
    ::println(cout, "The answer is {}.", 42);
    // ADL can find the wrong version with unqualified lookup
#endif
}
