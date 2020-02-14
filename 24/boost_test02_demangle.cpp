#include <iostream>
#include <typeinfo>
#include <utility>
#include <vector>
#include <boost/core/demangle.hpp>

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
