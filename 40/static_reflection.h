/*
 * MIT License
 *
 * Copyright (c) 2021 Netcan
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

#ifndef STATIC_REFLECTION_H
#define STATIC_REFLECTION_H

#include <cstddef>                // std::size_t
#include <cstdint>                // SIZE_MAX
#include <type_traits>            // std::is_same_v
#include <utility>                // std::forward/(make_)index_sequence
#include "compile_time_string.h"  // CTS_STRING
#include "metamacro.h"            // GET_ARG_COUNT/PAIR/PASTE/REPEAT_ON/STRIP

#define FIELD(i, arg)                                                      \
    PAIR(arg);                                                             \
    template <typename T>                                                  \
    struct _field<T, i> {                                                  \
        _field(T&& obj) : obj_(std::forward<T>(obj)) {} /* NOLINT */       \
        static constexpr auto name = CTS_STRING(STRIP(arg));               \
        using type = decltype(std::decay_t<T>::STRIP(arg));                \
        decltype(auto) value()                                             \
        {                                                                  \
            return (std::forward<T>(obj_).STRIP(arg));                     \
        }                                                                  \
        T&& obj_; /* NOLINT */                                             \
    };

#define DEFINE_STRUCT(st, ...)                                             \
    struct st {                                                            \
        template <typename, std::size_t>                                   \
        struct _field;                                                     \
        static constexpr std::size_t _size = GET_ARG_COUNT(__VA_ARGS__);   \
        REPEAT_ON(FIELD, __VA_ARGS__)                                      \
    }

// This macro can only be used at the global namespace, so it cannot be
// integrated into the DEFINE_STRUCT macro, even if the functionality is
// always wanted.
#define DECLARE_TUPLE_LIKE(st)                                             \
    template <>                                                            \
    struct std::tuple_size<st> {                                           \
        static constexpr size_t value = st::_size;                         \
    };                                                                     \
    template <size_t I>                                                    \
    struct std::tuple_element<I, st> {                                     \
        using type = typename st::_field<st, I>::type;                     \
    }

namespace sr {

template <typename T, typename = void>
struct is_reflected : std::false_type {
};

template <typename T>
struct is_reflected<T, std::void_t<decltype(T::_size)>> : std::true_type {
};

template <typename T>
inline constexpr static bool is_reflected_v = is_reflected<T>::value;

template <typename T>
struct type_wrapper {
    using type = T;
};

template <typename T, typename F, std::size_t... Is>
constexpr void for_each_meta_impl(F&& f, std::index_sequence<Is...>)
{
    using DT = std::decay_t<T>;
    (void(std::forward<F>(f)(
         Is, DT::template _field<T, Is>::name,
         type_wrapper<typename DT::template _field<T, Is>::type>{})),
     ...);
}

template <typename T, typename F,
          std::enable_if_t<is_reflected_v<T>, bool> = true>
constexpr void for_each_meta(F&& f)
{
    for_each_meta_impl<T>(std::forward<F>(f),
                          std::make_index_sequence<T::_size>{});
}

template <typename T, typename F, std::size_t... Is>
constexpr void for_each_impl(T&& obj, F&& f, std::index_sequence<Is...>)
{
    using DT = std::decay_t<T>;
    (void(std::forward<F>(f)(
         DT::template _field<T, Is>::name,
         typename DT::template _field<T, Is>(std::forward<T>(obj))
             .value())),
     ...);
}

template <typename T, typename F,
          std::enable_if_t<is_reflected_v<std::decay_t<T>>, bool> = true>
constexpr void for_each(T&& obj, F&& f)
{
    using DT = std::decay_t<T>;
    for_each_impl(std::forward<T>(obj), std::forward<F>(f),
                  std::make_index_sequence<DT::_size>{});
}

template <typename T, typename U, typename F, std::size_t... Is>
constexpr void zip_impl(T&& obj1, U&& obj2, F&& f,
                        std::index_sequence<Is...>)
{
    using DT = std::decay_t<T>;
    using DU = std::decay_t<U>;
    static_assert(DT::_size == DU::_size);
    (void(std::forward<F>(f)(
         DT::template _field<T, Is>::name, DU::template _field<U, Is>::name,
         typename DT::template _field<T, Is>(std::forward<T>(obj1)).value(),
         typename DU::template _field<U, Is>(std::forward<U>(obj2))
             .value())),
     ...);
}

template <typename T, typename U, typename F,
          std::enable_if_t<is_reflected_v<std::decay_t<T>> &&
                           is_reflected_v<std::decay_t<U>>,
                           bool> = true>
constexpr void zip(T&& obj1, U&& obj2, F&& f)
{
    using DT = std::decay_t<T>;
    using DU = std::decay_t<U>;
    static_assert(DT::_size == DU::_size);
    zip_impl(std::forward<T>(obj1), std::forward<U>(obj2),
             std::forward<F>(f), std::make_index_sequence<DT::_size>{});
}

template <typename T, typename U>
constexpr void copy(T&& src, U& dest)
{
    if constexpr (is_reflected_v<std::decay_t<T>> &&
                  is_reflected_v<std::decay_t<U>>) {
        zip(std::forward<T>(src), dest,
            [](auto /*field_name1*/, auto /*field_name1*/,
               auto&& value1, auto& value2) {
                copy(std::forward<decltype(value1)>(value1), value2);
            });
    } else {
        dest = std::forward<T>(src);
    }
}

template <typename T, typename Name,
          std::enable_if_t<is_reflected_v<T>, bool> = true>
constexpr std::size_t get_field_index(Name /*name*/)
{
    auto result = SIZE_MAX;
    for_each_meta<T>(
        [&result](std::size_t index, auto name, auto /*type*/) {
            if constexpr (std::is_same_v<decltype(name), Name>) {
                result = index;
            }
        });
    return result;
}

template <typename T, typename U,
          std::enable_if_t<is_reflected_v<std::decay_t<T>> &&
                           is_reflected_v<std::decay_t<U>>,
                           bool> = true>
constexpr std::size_t count_missing_fields()
{
    std::size_t result = 0;
    for_each_meta<U>(
        [&result](std::size_t /*index*/, auto name, auto /*type*/) {
            if constexpr (get_field_index<T>(name) == SIZE_MAX) {
                ++result;
            }
        });
    return result;
}

enum class missing_fields : std::size_t {};

template <missing_fields MissingFields = missing_fields{0},
         typename T, typename U>
constexpr void copy_same_name_fields(T&& src, U& dest) // NOLINT
{
    constexpr size_t actual_missing_fields =
        count_missing_fields<std::decay_t<T>, std::decay_t<U>>();
    static_assert(size_t(MissingFields) == actual_missing_fields);
    for_each(dest, [&src](auto field_name, auto& value) {
        using DT = std::decay_t<T>;
        constexpr auto field_index = get_field_index<DT>(field_name);
        if constexpr (field_index != SIZE_MAX) {
            copy(typename DT::template _field<T, field_index>(
                     std::forward<T>(src))
                     .value(),
                 value);
        }
    });
}

template <
    std::size_t I, typename T,
    std::enable_if_t<sr::is_reflected_v<std::decay_t<T>>, bool> = true>
decltype(auto) get(T&& obj)
{
    static_assert(I < std::decay_t<T>::_size,
                  "Index to get is out of range");
    return typename std::decay_t<T>::template _field<T, I>(
               std::forward<T>(obj))
        .value();
}

} // namespace sr

#endif // STATIC_REFLECTION_H
