#include <iostream>
#include <stdlib.h>

using namespace std;

// Can copy and move
class A {
public:
    A() { cout << "Create A\n"; }
    ~A() { cout << "Destroy A\n"; }
    A(const A&) { cout << "Copy A\n"; }
    A(A&&) { cout << "Move A\n"; }
};

A getA_duang()
{
    A a1;
    A a2;
    if (rand() > 42) {
        return a1;
    } else {
        return a2;
    }
}

int main()
{
    auto a = getA_duang();
}
