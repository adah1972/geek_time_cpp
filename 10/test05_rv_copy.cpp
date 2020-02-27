#include <iostream>  // std::cout
#include <stdlib.h>  // rand

using namespace std;

// Can copy, but not move
class A {
public:
    A() { cout << "Create A\n"; }
    ~A() { cout << "Destroy A\n"; }
    A(const A&) { cout << "Copy A\n"; }
    // A(A&&) { cout << "Move A\n"; }
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
