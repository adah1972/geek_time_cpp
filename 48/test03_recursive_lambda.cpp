#include <iostream>  // std::cout

#ifndef __has_extension
#define __has_extension(x) 0  // Compatibility with non-clang compilers.
#endif

int main()
{
#if __cpp_explicit_this_parameter >= 202110L ||                            \
    __has_extension(cxx_explicit_this_parameter) ||                        \
    (_MSC_VER >= 1932 && _MSVC_LANG >= 202302L)
    auto fac = [](this auto self, int n) {
        if (n <= 1) {
            return 1;
        } else {
            return n * self(n - 1);
        }
    };

    std::cout << fac(10) << '\n';
#else
    std::cout << "Explicit object parameter is not supported in your "
                 "environment\n";
#endif
}
