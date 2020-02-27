#include <iostream>                          // std::cout/endl/dec/hex
#include <boost/multiprecision/cpp_int.hpp>  // boost::multiprecision::cpp_int

using namespace std;

int main()
{
    using namespace boost::multiprecision::literals;
    using boost::multiprecision::cpp_int;

    cpp_int a = 0x123456789abcdef0_cppi;
    cpp_int b = 16;
    cpp_int c{"0400"};
    cpp_int result = a * b / c;
    cout << hex << result << endl;
    cout << dec << result << endl;
}
