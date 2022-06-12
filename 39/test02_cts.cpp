#include <cstddef>      // std::size_t
#include <cstdio>       // std::puts
#include <type_traits>  // std::is_same_v

#define CONCAT(x, y) x##y
#define PASTE(x, y) CONCAT(x, y)
#define STR(x) #x
#define STRING(x) STR(x)

#if __cplusplus >= 202002L || (defined(_MSVC_LANG) && _MSVC_LANG >= 202002L)

template <std::size_t N>
struct compile_time_string {
    // Including <algorithm> could be quite heavyweight, if we only need
    // to use copy_n
    static constexpr void copy_n(const char* src, std::size_t count,
                                 char* dest)
    {
        for (std::size_t i = 0; i < count; ++i) {
            dest[i] = src[i];
        }
    }
    consteval compile_time_string(const char (&str)[N])
    {
        copy_n(str, N, value);
    }
    char value[N]{};
};

template <compile_time_string cts>
constexpr auto operator""_cts()
{
    return cts;
}

template <compile_time_string cts>
struct cts_wrapper {
    static constexpr compile_time_string str{cts};
};

#define CTS_STRING(x)     cts_wrapper<STR(x)>{}
#define CTS_GET_VALUE(x)  (decltype(x)::str.value)

#elif defined(__GNUC__)

template <char... Cs>
struct compile_time_string {
    static constexpr char value[sizeof...(Cs) + 1]{Cs...};
};

#pragma GCC diagnostic push

#ifdef __clang__
#pragma GCC diagnostic ignored "-Wgnu-string-literal-operator-template"
#else
#pragma GCC diagnostic ignored "-Wpedantic"
#endif

// We here use the non-standard GCC string literal operator template that
// takes an argument pack of characters
template <typename T, T... Cs>
constexpr compile_time_string<Cs...> operator""_cts()
{
    return {};
}

#pragma GCC diagnostic pop

#define CTS_STRING(x)     PASTE(STR(x), _cts)
#define CTS_GET_VALUE(x)  ((x).value)

#else

#error "A C++20- or GCC-compatible compiler is required"

#endif

int main()
{
    using std::puts;

    using t1 = decltype(CTS_STRING(Hi));
    using t2 = decltype(CTS_STRING(Hi));
    using t3 = decltype(CTS_STRING(Ha));
    static_assert(std::is_same_v<t1, t2>);
    static_assert(!std::is_same_v<t1, t3>);

    puts(CTS_GET_VALUE(CTS_STRING(Hi)));
}
