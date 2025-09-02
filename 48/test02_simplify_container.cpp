#ifndef __has_extension
#define __has_extension(x) 0  // Compatibility with non-clang compilers.
#endif

#if __cpp_explicit_this_parameter >= 202110L ||                            \
    __has_extension(cxx_explicit_this_parameter) ||                        \
    (_MSC_VER >= 1932 && _MSVC_LANG >= 202302L)

#include <iostream>     // std::cout
#include <type_traits>  // std::is_const/remove_const/remove_reference

using namespace std;

template <typename T, typename U>
constexpr auto forward_pointer_like(U* ptr)
{
    constexpr bool is_adding_const = is_const_v<remove_reference_t<T>>;
    if constexpr (is_adding_const != is_const_v<U>) {
        if constexpr (is_adding_const) {
            return const_cast<const U*>(ptr);
        } else {
            return const_cast<remove_const_t<U>*>(ptr);
        }
    } else {
        return ptr;
    }
}

template <typename T>
class Container {
public:
    template <typename Self>
    // NOLINTNEXTLINE(cppcoreguidelines-missing-std-forward)
    auto data(this Self&& self) noexcept
    {
        return forward_pointer_like<Self>(self.data_);
    }

private:
    T* data_{};
};

int main()
{
    Container<int> c1;
    const Container<int> c2;
    static_assert(
        !std::is_const_v<std::remove_reference_t<decltype(*c1.data())>>);
    static_assert(
        std::is_const_v<std::remove_reference_t<decltype(*c2.data())>>);
    std::cout << "All tests pass\n";
}

#else

#include <iostream>  // std::cout

int main()
{
    std::cout << "Explicit object parameter is not supported in your "
                 "environment\n";
}

#endif
