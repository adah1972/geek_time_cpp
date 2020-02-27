#include <iostream>                  // std::cout/endl
#include <stdint.h>                  // uint64_t
#include <boost/coroutine2/all.hpp>  // boost::coroutines2

typedef boost::coroutines2::coroutine<const uint64_t> coro_t;

void fibonacci(coro_t::push_type& yield)
{
    uint64_t a = 0;
    uint64_t b = 1;
    while (true) {
        yield(b);
        auto tmp = a;
        a = b;
        b += tmp;
    }
}

int main()
{
    for (auto i : coro_t::pull_type(
             boost::coroutines2::fixedsize_stack(),
             fibonacci)) {
        if (i >= 10000) {
            break;
        }
        std::cout << i << std::endl;
    }
}
