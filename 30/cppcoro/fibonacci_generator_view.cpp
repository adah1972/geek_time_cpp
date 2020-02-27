#include <experimental/ranges/ranges>  // ranges::views
#include <iostream>                    // std::cout/endl
#include <stdint.h>                    // uint64_t
#include <cppcoro/generator.hpp>       // cppcoro::generator

using cppcoro::generator;

generator<uint64_t> fibonacci()
{
    uint64_t a = 0;
    uint64_t b = 1;
    while (true) {
        co_yield b;
        auto tmp = a;
        a = b;
        b += tmp;
    }
}

int main()
{
    namespace ranges = std::experimental::ranges;
    auto&& fib = fibonacci();
    // A view does not work with an rvalue, so we need to assign
    // fibonacci() to a reference.
    for (auto i : fib | ranges::views::take(20)) {
        std::cout << i << std::endl;
    }
}
