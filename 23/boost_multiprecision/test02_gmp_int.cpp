#include <iostream>                      // std::cout/endl/dec/hex
#include <boost/multiprecision/gmp.hpp>  // boost::multiprecision::gmp_int

using namespace std;

int main()
{
    typedef boost::multiprecision::number<boost::multiprecision::gmp_int,
                                          boost::multiprecision::et_off>
        int_type;

    int_type a{"0x123456789abcdef0"};
    int_type b = 16;
    int_type c{"0400"};
    int_type result = a * b / c;
    cout << hex << result << endl;
    cout << dec << result << endl;
}
