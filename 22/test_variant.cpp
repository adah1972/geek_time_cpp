#include <nvwa/c++_features.h>
#if NVWA_USES_CRIPPLED_CLANG
#include <__config>
#undef  _LIBCPP_AVAILABILITY_BAD_VARIANT_ACCESS
#define _LIBCPP_AVAILABILITY_BAD_VARIANT_ACCESS
#endif

#include <iostream>
#include <string>
#include <variant>

using namespace std;

int main()
{
    variant<string, int, char> obj{"Hello world"};
    cout << get<string>(obj) << endl;
}
