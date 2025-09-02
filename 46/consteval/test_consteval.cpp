#include <iostream>   // std::cout
#include <stdexcept>  // std::invalid_argument

#if __cpp_consteval >= 201811L || __clang_major__ >= 11

consteval int check(int value)
{
    if (value < 1 || value > 42) {
        throw std::invalid_argument("invalid value");
    }
    return value;
}

constexpr void doSomething(int value)
{
    (void)value;
}

int main()
{
    doSomething(check(42));

    // Uncomment to see compilation errors
    // doSomething(check(43));
}

#else

int main()
{
    std::cout << "consteval is not supported in your environment\n";
}

#endif
