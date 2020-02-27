#include <algorithm>           // std::sort
#include <functional>          // std::less/greater/hash
#include <iostream>            // std::cout/endl
#include <string>              // std::string
#include <vector>              // std::vector
#include "output_container.h"  // operator<< for containers

using namespace std;

int main()
{
    vector<int> v{13, 6, 4, 11, 29};
    cout << v << endl;

    sort(v.begin(), v.end());
    cout << v << endl;

    sort(v.begin(), v.end(), greater<int>());
    cout << v << endl;

    cout << hex;

    auto hp = hash<int*>();
    cout << "hash(nullptr)  = " << hp(nullptr) << endl;
    cout << "hash(v.data()) = " << hp(v.data()) << endl;
    cout << "v.data()       = " << static_cast<void*>(v.data()) << endl;

    auto hs = hash<string>();
    cout << "hash(\"hello\")  = " << hs(string("hello")) << endl;
    cout << "hash(\"hellp\")  = " << hs(string("hellp")) << endl;
}
