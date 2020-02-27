#define CATCH_CONFIG_MAIN
#include "catch.hpp"  // TEST_CASE/CHECK/INFO/...
#include <stdexcept>  // std::runtime_error

void test(int n)
{
    if (n == 42) {
        return;
    }
    throw std::runtime_error("Not the answer");
}

TEST_CASE("My first test", "[my][test]")
{
    INFO("Testing");
    CHECK(1 + 1 == 2);
    CHECK_THROWS_AS(test(41), std::runtime_error);
    CHECK_NOTHROW(test(42));

    int expected = 5;
    CHECK(2 + 2 == expected);
}

TEST_CASE("A null test", "[null][test]")
{
}
