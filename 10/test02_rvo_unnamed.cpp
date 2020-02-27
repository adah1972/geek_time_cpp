#include <iostream>  // std::cout

using namespace std;

// No copy and move
class A {
public:
    A() { cout << "Create A\n"; }
    ~A() { cout << "Destroy A\n"; }
    A(const A&) = delete;
    A(A&&) = delete;
};

A getA_unnamed()
{
    return A();
}

int main()
{
    auto a = getA_unnamed();
}
