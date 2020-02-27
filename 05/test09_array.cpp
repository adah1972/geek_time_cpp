#include <array>               // std::array
#include <iostream>            // std::cout/endl
#include <map>                 // std::map
#include "output_container.h"  // operator<< for containers

typedef std::array<char, 8> mykey_t;

int main()
{
    std::map<mykey_t, int> mp;
    mykey_t mykey{"hello"};
    mp[mykey] = 5;  // OK
    std::cout << mp << std::endl;
}
