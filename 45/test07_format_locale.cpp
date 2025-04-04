#include <iostream>      // std::cout
#include <chrono>        // std::chrono::*
#include <locale>        // std::locale
#include <stdexcept>     // std::runtime_error
#if __has_include(<version>)
#include <version>       // __cpp_lib_format/__cpp_lib_print
#endif

#define TEST_FORMAT_STD 1
#define TEST_FORMAT_FMT 2

#ifndef TEST_FORMAT
#if __cpp_lib_format >= 201907L ||                                         \
    (__cplusplus >= 202002L && _LIBCPP_VERSION >= 170000)
#define TEST_FORMAT TEST_FORMAT_STD
#elif __has_include(<fmt/format.h>)
#define TEST_FORMAT TEST_FORMAT_FMT
#endif
#endif

#if TEST_FORMAT == TEST_FORMAT_STD
#include <format>        // std::format
using std::format;
#if __cpp_lib_print >= 202207L
#include <print>         // std::println
using std::println;
#endif
#elif TEST_FORMAT == TEST_FORMAT_FMT
#include <fmt/format.h>  // fmt::format
using fmt::format;
#endif

using std::cout;
using std::locale;
using std::chrono::system_clock;

#if _WIN32

constexpr auto en_loc_name = "English_America.65001";
constexpr auto de_loc_name = "German_Germany.65001";
constexpr auto zh_loc_name = "Chinese_China.65001";

#else

constexpr auto en_loc_name = "en_US.UTF-8";
constexpr auto de_loc_name = "de_DE.UTF-8";
constexpr auto zh_loc_name = "zh_CN.UTF-8";

#endif

int main()
{
    locale en_loc;
    locale de_loc;
    try {
        en_loc = locale{en_loc_name};
        cout << "en_loc is successfully set to US English\n";
        de_loc = locale{de_loc_name};
        cout << "de_loc is successfully set to German\n";
        locale::global(locale{zh_loc_name});
        cout << "Global locale is successfully set to Chinese\n";
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
    }

    cout << ::format(        "In C locale:       {:.3f}\n", 12345.67);
    cout << ::format(        "In global locale:  {:.3Lf}\n", 12345.67);
    cout << ::format(en_loc, "In USA locale:     {:.3Lf}\n", 12345.67);
    cout << ::format(de_loc, "In Germany locale: {:.3Lf}\n", 12345.67);

    // {fmt} does not support locale-formatted date and time
#if TEST_FORMAT == TEST_FORMAT_STD
#if __cpp_lib_print >= 202207L
    println("In C locale:       {:%x}", system_clock::now());
    println("In global locale:  {:L%x}", system_clock::now());
#else
    cout << ::format("In C locale:       {:%x}\n", system_clock::now());
    cout << ::format("In global locale:  {:L%x}\n", system_clock::now());
#endif
#endif
}
