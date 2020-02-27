#include "catch.hpp"  // SCENARIO/GIVEN/WHEN/THEN/CHECK
#include <vector>     // std::vector

typedef std::vector<int> IntContainer;

SCENARIO("Int container can be accessed and modified", "[container]")
{
    GIVEN("A container with initialized items")
    {
        IntContainer c{1, 2, 3, 4, 5};
        REQUIRE(c.size() == 5);

        WHEN("I access existing items")
        {
            THEN("The items can be retrieved intact")
            {
                CHECK(c[0] == 1);
                CHECK(c[1] == 2);
                CHECK(c[2] == 3);
                CHECK(c[3] == 4);
                CHECK(c[4] == 5);
            }
        }

        WHEN("I modify items")
        {
            c[1] = -2;
            c[3] = -4;

            THEN("Only modified items are changed")
            {
                CHECK(c[0] == 1);
                CHECK(c[1] == -2);
                CHECK(c[2] == 3);
                CHECK(c[3] == -4);
                CHECK(c[4] == 5);
            }
        }
    }
}
