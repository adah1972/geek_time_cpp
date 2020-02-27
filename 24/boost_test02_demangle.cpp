#include <iostream>                 // std::cout/endl
#include <typeinfo>                 // std::type_info
#include <vector>                   // std::vector
#include <boost/core/demangle.hpp>  // boost::core::demangle

using namespace std;
using boost::core::demangle;

int main()
{
    vector<int> v;
    auto it = v.cbegin();

    cout << "*** Using typeid\n";
    cout << typeid(const int).name() << endl;
    cout << typeid(v).name() << endl;
    cout << typeid(it).name() << endl;

    cout << "*** Demangled\n";
    cout << demangle(typeid(const int).name()) << endl;
    cout << demangle(typeid(v).name()) << endl;
    cout << demangle(typeid(it).name()) << endl;
}
