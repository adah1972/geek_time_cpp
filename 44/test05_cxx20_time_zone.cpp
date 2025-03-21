#include <chrono>     // std::chrono::*
#include <exception>  // std::exception
#include <iostream>   // std::cout

using namespace std::chrono;
using std::cout;
using std::exception;

int main()
{
#if __cpp_lib_chrono >= 201907L ||                                         \
    (__cplusplus >= 202002L && ((!defined(__clang__) && __GNUC__ >= 13)))
    auto sys_tp = sys_days{2025y/3/9} + 9h + 59min + 59s;
    auto* local_tz = get_tzdb().current_zone();
    auto zoned_tp = zoned_time{local_tz, sys_tp};

    cout << "sizeof sys_tp:   " << sizeof sys_tp << '\n';
    cout << "sizeof zoned_tp: " << sizeof zoned_tp << '\n';

    cout << sys_tp << '\n';
    cout << zoned_tp << '\n';

    auto* pst_tz = get_tzdb().locate_zone("US/Pacific");
    auto pst_tp = zoned_time{pst_tz, sys_tp};
    cout << pst_tp << '\n';
    pst_tp = zoned_time{pst_tz, sys_tp + 1s};
    cout << pst_tp << '\n';

    try {
        auto local_tp = local_days{2025y/3/9} + 2h;
        pst_tp = zoned_time{pst_tz, local_tp};
        cout << pst_tp << '\n';
    }
    catch (const exception& e) {
        cout << "*** Error: " << e.what() << '\n';
    }
    try {
        auto local_tp = local_days{2025y/11/2} + 1h;
        pst_tp = zoned_time{pst_tz, local_tp};
        cout << pst_tp << '\n';
    }
    catch (const exception& e) {
        cout << "*** Error: " << e.what() << '\n';
    }
    try {
        auto local_tp = local_days{2025y/11/2} + 1h;
        pst_tp = zoned_time{pst_tz, local_tp, choose::latest};
        cout << pst_tp << '\n';
    }
    catch (const exception& e) {
        cout << "*** Error: " << e.what() << '\n';
    }
#else
    cout << "C++20 chrono is not fully supported in your environment\n";
#endif
}
