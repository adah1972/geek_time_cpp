#include <nvwa/c++_features.h>  // NVWA_USES_CRIPPLED_CLANG
#if NVWA_USES_CRIPPLED_CLANG
#include <__config>
#undef  _LIBCPP_AVAILABILITY_BAD_OPTIONAL_ACCESS
#define _LIBCPP_AVAILABILITY_BAD_OPTIONAL_ACCESS
#endif

#include <functional>   // std::plus
#include <iostream>     // std::cout/endl
#include <optional>     // std::optional/make_optional
#include <type_traits>  // std::decay_t
#include <utility>      // std::forward

using namespace std;

template <typename T>
constexpr bool has_value(const optional<T>& x) noexcept
{
    return x.has_value();
}

template <typename T, typename... Args>
constexpr bool has_value(const optional<T>& first,
                         const optional<Args>&... other) noexcept
{
    return first.has_value() && has_value(other...);
}

template <typename F>
auto lift_optional(F&& f)
{
    return [f = std::forward<F>(f)](auto&&... args) {
        typedef decay_t<decltype(
            f(std::forward<decltype(args)>(args).value()...))>
            result_type;
        if (has_value(args...)) {
            return optional<result_type>(
                f(std::forward<decltype(args)>(args).value()...));
        } else {
            return optional<result_type>();
        }
    };
}

constexpr int increase(int n)
{
    return n + 1;
}

ostream& operator<<(ostream& os, optional<int>(x))
{
    if (x) {
        os << '(' << *x << ')';
    } else {
        os << "(Nothing)";
    }
    return os;
}

int main()
{
    auto inc_opt = lift_optional(increase);
    auto plus_opt = lift_optional(plus<int>());
    cout << inc_opt(optional<int>()) << endl;
    cout << inc_opt(make_optional(41)) << endl;
    cout << plus_opt(make_optional(41), optional<int>()) << endl;
    cout << plus_opt(make_optional(41), make_optional(1)) << endl;
}
