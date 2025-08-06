#include <iostream>     // std::cout

using namespace std;

#if __has_include(<version>)
#include <version>      // __cpp_lib_bit_cast
#endif

#if __cpp_lib_bit_cast >= 201806L

#include <bit>          // std::bit_cast

#else

#include <type_traits>  // std::enable_if/is_trivially_copyable/...
#include <string.h>     // memcpy

template <class To, class From>
enable_if_t<(sizeof(To) == sizeof(From) &&
             is_trivially_copyable_v<From> &&
             is_trivially_copyable_v<To>),
            To>
bit_cast(const From& src) noexcept
{
    static_assert(is_trivially_constructible_v<To>,
                  "This implementation additionally requires destination "
                  "type to be trivially constructible");
    To dst;
    memcpy(&dst, &src, sizeof(To));
    return dst;
}

#endif

int main()
{
    unsigned char data[sizeof(float)]{0x00, 0x00, 0x40, 0x40};
    auto f = bit_cast<float>(data);
    cout << f << '\n';
}
