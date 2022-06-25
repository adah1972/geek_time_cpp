/*
 * Written by Wu Yongwei <wuyongwei AT gmail DOT com>.
 *
 * Using this file requires a C++17-compliant compiler.
 *
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://unlicense.org>
 *
 */

#ifndef OUTPUT_RANGE_H
#define OUTPUT_RANGE_H

#include <cstddef>      // std::byte
#include <iterator>     // std::begin/end
#include <ostream>      // std::ostream
#include <tuple>        // std::tuple/tuple_size
#include <type_traits>  // std::false_type/true_type/decay_t/is_same_v/remove_...
#include <utility>      // std::declval/forward/pair

#ifndef OUTPUT_RANGE_NO_STRING_QUOTE
#include <string>       // std::string
#include <string_view>  // std::string_view
#endif

namespace output_range {

using std::begin;
using std::end;

template <class Rng>
auto adl_begin(Rng&& rng) -> decltype(begin(rng))
{
    // Intentionally not using std::forward, as std::begin does not
    // accept an rvalue reference.
    return begin(rng);
}

template <class Rng>
auto adl_end(Rng&& rng) -> decltype(end(rng))
{
    // Intentionally not using std::forward, as std::end does not
    // accept an rvalue reference.
    return end(rng);
}

// Type trait to detect std::pair
template <typename T>
struct is_pair : std::false_type {};
template <typename T, typename U>
struct is_pair<std::pair<T, U>> : std::true_type {};
template <typename T>
inline constexpr bool is_pair_v = is_pair<T>::value;

// Type trait for tuple-like objects
template <typename T, typename = void>
struct is_tuple_like : std::false_type {};
template <typename T>
struct is_tuple_like<T, std::void_t<decltype(std::tuple_size<T>::value)>>
    : std::true_type {};
template <typename T>
inline constexpr bool is_tuple_like_v = is_tuple_like<T>::value;

// Type trait to detect whether an output function already exists
template <typename T>
struct has_output_function {
    template <class U>
    static auto output(U* ptr)
        -> decltype(std::declval<std::ostream&>() << *ptr,
                    std::true_type{});
    template <class U>
    static std::false_type output(...);
    static constexpr bool value =
        decltype(output<T>(nullptr))::value;
};
#ifndef OUTPUT_RANGE_NO_ARRAY_OUTPUT
template <typename T, std::size_t N>
struct has_output_function<T[N]> : std::false_type {};
template <std::size_t N>
struct has_output_function<char[N]> : std::true_type {};
template <std::size_t N>
struct has_output_function<signed char[N]> : std::true_type {};
template <std::size_t N>
struct has_output_function<unsigned char[N]> : std::true_type {};
template <std::size_t N>
struct has_output_function<const char[N]> : std::true_type {};
template <std::size_t N>
struct has_output_function<const signed char[N]> : std::true_type {};
template <std::size_t N>
struct has_output_function<const unsigned char[N]> : std::true_type {};
#endif
template <typename T>
inline constexpr bool has_output_function_v =
    has_output_function<T>::value;

// Element output function for containers that define a key_type and
// have its value type as std::pair
template <typename T, typename Rng>
auto output_element(std::ostream& os, const T& element,
                    const Rng&, std::true_type)
    -> decltype(std::declval<typename Rng::key_type>(), os);
// Element output function for other containers
template <typename T, typename Rng>
auto output_element(std::ostream& os, const T& element,
                    const Rng&, ...)
    -> decltype(os);

// Member output function for tuple-like objects
template <typename Tup, std::size_t... Is>
void output_tuple_members(std::ostream& os, const Tup& tup,
                          std::index_sequence<Is...>);

}  // namespace output_range

// Output function for tuple-like objects
template <typename T,
          std::enable_if_t<output_range::is_tuple_like_v<T>, bool> = true>
std::ostream& operator<<(std::ostream& os, const T& tup);

// Main output function, enabled only if no output function already exists
template <
    typename Rng,
    std::enable_if_t<!output_range::has_output_function_v<
                         std::remove_cv_t<std::remove_reference_t<Rng>>>,
                     bool> = true>
auto operator<<(std::ostream& os, Rng&& rng)
    -> decltype(output_range::adl_begin(std::forward<Rng>(rng)),
                output_range::adl_end(std::forward<Rng>(rng)), os)
{
    using std::decay_t;
    using std::is_same_v;

    using element_type =
        decay_t<decltype(*output_range::adl_begin(std::forward<Rng>(rng)))>;
    os << '{';
    auto end = output_range::adl_end(std::forward<Rng>(rng));
    bool on_first_element = true;
    for (auto it = output_range::adl_begin(std::forward<Rng>(rng));
         it != end; ++it) {
        if (!on_first_element) {
            os << ", ";
        } else {
            os << ' ';
            on_first_element = false;
        }
        output_range::output_element(os, *it, std::forward<Rng>(rng),
                                     output_range::is_pair<element_type>{});
    }
    if (!on_first_element) {  // Not empty
        os << ' ';
    }
    os << '}';
    return os;
}

template <typename T,
          std::enable_if_t<output_range::is_tuple_like_v<T>, bool>>
std::ostream& operator<<(std::ostream& os, const T& tup)
{
    os << '(';
    output_range::output_tuple_members(
        os, tup, std::make_index_sequence<std::tuple_size_v<T>>{});
    os << ')';
    return os;
}

namespace output_range {

template <typename T, typename Rng>
auto output_element(std::ostream& os, const T& element, const Rng&,
                    std::true_type)
    -> decltype(std::declval<typename Rng::key_type>(), os)
{
    output_element(os, element.first, element);
    os << " => ";
    output_element(os, element.second, element);
    return os;
}

template <typename T, typename Rng>
auto output_element(std::ostream& os, const T& element, const Rng&,
                    ...)
    -> decltype(os)
{
    if constexpr (std::is_same_v<T, char> ||
                  std::is_same_v<T, signed char>) {
        os << '\'' << element << '\'';
    } else if constexpr (std::is_same_v<T, unsigned char> ||
                         std::is_same_v<T, std::byte>) {
        os << static_cast<unsigned>(element);
    } else
#ifndef OUTPUT_RANGE_NO_STRING_QUOTE
    {
        using DT = std::decay_t<T>;
        using PT = std::remove_cv_t<std::remove_pointer_t<DT>>;
        if constexpr (std::is_same_v<T, std::string> ||
                      std::is_same_v<T, std::string_view> ||
                      (std::is_pointer_v<DT> &&
                       (std::is_same_v<PT, char> ||
                        std::is_same_v<PT, signed char> ||
                        std::is_same_v<PT, unsigned char>))) {
            os << '"' << element << '"';
        } else {
            os << element;
        }
    }
#else
    {
        os << element;
    }
#endif
    return os;
}

template <typename Tup, std::size_t... Is>
void output_tuple_members(std::ostream& os, const Tup& tup,
                          std::index_sequence<Is...>)
{
    using std::get;
    ((os << (Is != 0 ? ", " : ""), output_element(os, get<Is>(tup), tup)),
     ...);
}

}  // namespace output_range

#endif  // OUTPUT_RANGE_H
