#include <chrono>    // std::chrono::*
#include <iostream>  // std::cout
#include <thread>    // std::this_thread::sleep_for

namespace this_thread = std::this_thread;
using namespace std::chrono;
using std::cout;

int main()
{
#if __cpp_lib_chrono >= 201907L ||                                         \
    (__cplusplus >= 202002L && ((!defined(__clang__) && __GNUC__ >= 13) || \
                                _LIBCPP_VERSION >= 170000))
    auto tp = system_clock::now();
    cout << tp << '\n';
    this_thread::sleep_for(100ms);
    cout << duration_cast<milliseconds>(system_clock::now() - tp) << '\n';
#else
    cout << "C++20 chrono is not fully supported in your environment\n";
#endif
}
