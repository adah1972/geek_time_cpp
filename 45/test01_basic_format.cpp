#include <iostream>      // std::cout
#if __has_include(<version>)
#include <version>       // __cpp_lib_format
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
#elif TEST_FORMAT == TEST_FORMAT_FMT
#include <fmt/format.h>  // fmt::format
using fmt::format;
#endif

#if TEST_FORMAT

using std::cout;

void printCharDecHex(char c)
{
    cout << format("'{0}': {0:3d} (0x{0:02X})\n", c);
}

int main()
{
    char msg[]{"Hello"};
    for (char c : msg) {
        if (c == '\0') {
            break;
        }
        printCharDecHex(c);
    }
}

#else

int main()
{
    std::cout << "No working format is found in your environment\n";
}

#endif
