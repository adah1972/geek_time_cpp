#include <iostream>  // std::cout
#include <utility>   // std::make_index_sequence

using namespace std;

constexpr int count_bits(unsigned char value)
{
    if (value == 0) {
        return 0;
    } else {
        return (value & 1) + count_bits(value >> 1);
    }
}

template <size_t... V>
struct bit_count_t {
    unsigned char count[sizeof...(V)] = {
        static_cast<unsigned char>(count_bits(V))...};
};

template <size_t... V>
constexpr bit_count_t<V...> get_bit_count(index_sequence<V...>)
{
    return bit_count_t<V...>();
}

auto bit_count = get_bit_count(make_index_sequence<256>());

int main()
{
    for (int i = 0; i < 16; ++i) {
        cout << static_cast<unsigned>(bit_count.count[i]) << '\n';
    }
}
