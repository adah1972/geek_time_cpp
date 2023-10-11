/*
 * MIT License
 *
 * Copyright (c) 2022-2023 Wu Yongwei
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
 * NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef COMPILE_TIME_STRING_H
#define COMPILE_TIME_STRING_H

#include <cstddef>      // std::size_t
#include "metamacro.h"  // PASTE/STR

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
#define CTS_GET_VALUE(x)  (std::remove_cvref_t<decltype(x)>::str.value)

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
#define CTS_GET_VALUE(x)  (std::decay_t<decltype(x)>::value)

#else

#error "A C++20- or GCC-compatible compiler is required"

#endif

#endif // COMPILE_TIME_STRING_H
