#include <iostream>

using namespace std;

// Can copy and move
class A {
public:
    A() { cout << "Create A\n"; }
    ~A() { cout << "Destroy A\n"; }
    A(const A&) { cout << "Copy A\n"; }
    A(A&&) { cout << "Move A\n"; }
};

A getA_named()
{
    A a;
    return a;
}

int main()
{
    auto a = getA_named();
}
