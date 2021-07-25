#include <tuple>        // std::tuple/make_tuple/get
#include <type_traits>  // std::remove_reference_t
#include <utility>      // std::forward
#include <stddef.h>     // size_t
#include <stdio.h>      // printf

template <class T, T... Ints>
struct integer_sequence {};

template <size_t... Ints>
using index_sequence = integer_sequence<size_t, Ints...>;

template <size_t N, size_t... Ints>
struct index_sequence_helper {
    typedef
        typename index_sequence_helper<N - 1, N - 1, Ints...>::type type;
};

template <size_t... Ints>
struct index_sequence_helper<0, Ints...> {
    typedef index_sequence<Ints...> type;
};

template <size_t N>
using make_index_sequence = typename index_sequence_helper<N>::type;

template <class F, class Tuple, size_t... I>
constexpr decltype(auto) apply_impl(F&& f, Tuple&& t, index_sequence<I...>)
{
    return f(std::get<I>(std::forward<Tuple>(t))...);
}

template <class F, class Tuple>
constexpr decltype(auto)
apply(F&& f, Tuple&& t)
{
    return apply_impl(
        std::forward<F>(f), std::forward<Tuple>(t),
        make_index_sequence<
            std::tuple_size_v<std::remove_reference_t<Tuple>>>{});
}

int main()
{
    auto tup = std::make_tuple("Hell%d %s!\n", 0, "world");
    // Force to use our version of apply, but not std::apply
    ::apply(printf, tup);
}
