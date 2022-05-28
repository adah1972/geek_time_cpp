#include <iostream>  // std::cout/endl
#include <ostream>   // std::ostream
#include <tuple>     // std::get/tuple/make_tuple
#include <utility>   // std::index_sequence/index_sequence_for

using namespace std;

template <typename... Args>
void print_all(const Args&... args)
{
    (cout << ... << args);
    cout << endl;
}

template <typename T, typename First, typename... Rest>
void print_with_separator(const T& sep, const First& first,
                          const Rest&... rest)
{
    cout << first;
    ((cout << sep << rest), ...);
    cout << endl;
}

template <typename Tup, size_t... Is>
void output_tuple_members(ostream& os, const Tup& tup,
                          index_sequence<Is...>)
{
    ((os << (Is != 0 ? ", " : "") << get<Is>(tup)), ...);
}

template <typename... Args>
void print_tuple(const tuple<Args...>& args)
{
    cout << '(';
    output_tuple_members(cout, args, index_sequence_for<Args...>{});
    cout << ')';
}

int main()
{
    print_all(1, 2, 3);
    print_with_separator(", ", 1, 2, 3);
    print_tuple(make_tuple(1, "two", 3.14159));
    cout << endl;
}
