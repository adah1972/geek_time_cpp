#ifndef __has_extension
#define __has_extension(x) 0  // Compatibility with non-clang compilers.
#endif

#if __cpp_explicit_this_parameter >= 202110L ||                            \
    __has_extension(cxx_explicit_this_parameter) ||                        \
    (_MSC_VER >= 1932 && _MSVC_LANG >= 202302L)

#include <ios>                   // std::boolalpha
#include <iostream>              // std::cout
#include <new>                   // IWYU pragma: keep for placement new
#include <type_traits>           // std::is_trivially_destructible
#include <utility>               // std::forward/swap

#if __has_include(<boost/type_index.hpp>)
#include <boost/type_index.hpp>  // boost::typeindex::type_id_with_cvr
using boost::typeindex::type_id_with_cvr;
#endif

template <typename T>
class optional {
public:
    typedef T value_type;

    constexpr optional() noexcept : dummy_() {}
    constexpr explicit optional(const T& x) : value_(x), engaged_(true) {}
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
    constexpr optional(const optional& rhs) : engaged_(rhs.engaged_)
    {
        if (engaged_) {
            new (&value_) T(rhs.value_);
        }
    }
    constexpr optional& operator=(const optional& rhs)
    {
        using std::swap;
        optional temp(rhs);
        swap(*this, temp);
        return *this;
    }

    constexpr ~optional() = default;
    constexpr ~optional()
        requires(!std::is_trivially_destructible_v<T>)
    {
        reset();
    }

    constexpr void reset() noexcept
    {
        if (engaged_) {
            value_.~T();
            engaged_ = false;
        }
    }

    constexpr bool has_value() const noexcept { return engaged_; }

    template <typename Self>
    constexpr auto&& operator*(this Self&& self) noexcept
    {
        return std::forward<Self>(self).value_;
    }

private:
    union {
        char dummy_;
        value_type value_;
    };
    bool engaged_{};
};

template <typename T>
void print_optional(const optional<T>& opt)
{
    std::cout << '(';
    if (opt.has_value()) {
        std::cout << *opt;
    }
    std::cout << ')';
    //*opt = T{}; // Cannot compile
}

int main()
{
    optional<int> opt1;
    optional<int> opt2{42};
    print_optional(opt1);
    std::cout << '\n';
    print_optional(opt2);
    std::cout << '\n';

    std::cout << std::boolalpha
              << std::is_trivially_destructible_v<optional<int>> << '\n';

#if __has_include(<boost/type_index.hpp>)
    std::cout << type_id_with_cvr<decltype(opt1)>().pretty_name() << '\n';
    std::cout << type_id_with_cvr<decltype(*opt1)>().pretty_name() << '\n';
    std::cout
        << type_id_with_cvr<decltype(*std::move(opt1))>().pretty_name()
        << '\n';
#endif
}

#else

#include <iostream>  // std::cout

int main()
{
    std::cout << "Explicit object parameter is not supported in your "
                 "environment\n";
}

#endif
