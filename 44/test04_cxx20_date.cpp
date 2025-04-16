#include <chrono>       // std::chrono::*
#include <iostream>     // std::cout
#include <type_traits>  // std::is_same

using namespace std::chrono;
using std::cout;

#if __cpp_lib_chrono >= 201907L ||                                         \
    (__cplusplus >= 202002L && ((!defined(__clang__) && __GNUC__ >= 13) || \
                                _LIBCPP_VERSION >= 170000))

template <typename T>
struct is_sys_time : std::false_type {};
template <typename Duration>
struct is_sys_time<sys_time<Duration>> : std::true_type {};
template <typename T>
inline constexpr bool is_sys_time_v = is_sys_time<T>::value;

int main()
{
    cout << 2025y/3/10 << '\n';
    cout << 2025y/March/10d << '\n';
    cout << 10d/3/2025y << '\n';
    cout << March/10/2025 << '\n';
    cout << Sunday[2]/5/2025 << '\n';
    cout << sys_days{2025y/May/Sunday[2]} << '\n';
    cout << 2025y/5/last << '\n';
    cout << sys_days{2025y/5/last} << '\n';
    cout << sys_days{2025y/5/last + months{1}} << '\n';
    cout << sys_days{2025y/5/last} + months{1} << '\n';
    cout << floor<days>(sys_days{2025y/5/last} + months{1}) << '\n';
    cout << sys_days{2025y/3/10} + 16h + 30min << '\n';

    static_assert(std::is_same_v<decltype(2025y/3/10), year_month_day>);
    static_assert(std::is_same_v<decltype(2025y/May/Sunday[2]),
                                 year_month_weekday>);
    static_assert(std::is_same_v<decltype(2025y/5/last),
                                 year_month_day_last>);
    static_assert(
        is_sys_time_v<decltype(sys_days{2025y/5/last} + months{1})>);
}

#else

int main()
{
    cout << "C++20 chrono is not fully supported in your environment\n";
}

#endif
