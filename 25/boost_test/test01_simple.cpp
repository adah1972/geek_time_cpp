#define BOOST_TEST_MAIN
#include <stdexcept>                 // std::runtime_error
#include <boost/test/unit_test.hpp>  // BOOST_TEST/...

void test(int n)
{
    if (n == 42) {
        return;
    }
    throw std::runtime_error("Not the answer");
}

BOOST_AUTO_TEST_CASE(my_test)
{
    BOOST_TEST_MESSAGE("Testing");
    BOOST_TEST(1 + 1 == 2);
    BOOST_CHECK_THROW(test(41), std::runtime_error);
    BOOST_CHECK_NO_THROW(test(42));

    int expected = 5;
    BOOST_TEST(2 + 2 == expected);
    BOOST_CHECK(2 + 2 == expected);
}

BOOST_AUTO_TEST_CASE(null_test)
{
}
