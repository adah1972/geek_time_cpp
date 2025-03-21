#include <chrono>    // std::chrono::*
#include <iostream>  // std::cout

using namespace std::chrono;
using std::cout;

int main()
{
#if __cpp_lib_chrono >= 201907L ||                                         \
    (__cplusplus >= 202002L && ((!defined(__clang__) && __GNUC__ >= 13)))
    auto* tz_ptr = get_tzdb().locate_zone("Asia/Shanghai");
    cout << "China observed daylight saving in the following years:\n";
    int count = 0;
    for (auto yr = 1980y; yr != 2000y; ++yr) {
        auto local_tp = local_days{yr/June/1};
        auto sys_tp = sys_days{yr/June/1};
        auto diff = sys_tp - tz_ptr->to_sys(local_tp);
        if (diff != 8h) {
            cout << yr << '\n';
            ++count;
        }
    }
    if (count != 6) {
        cout << "Your time zone database is incomplete\n";
    }
#else
    cout << "C++20 chrono is not fully supported in your environment\n";
#endif
}
