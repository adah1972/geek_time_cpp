#include <iostream>                // std::cout/endl
#include <stdint.h>                // uint64_t
#include <experimental/generator>  // generator

using std::experimental::generator;

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
    for (auto i : fibonacci()) {
        if (i >= 10000) {
            break;
        }
        std::cout << i << std::endl;
    }
}
