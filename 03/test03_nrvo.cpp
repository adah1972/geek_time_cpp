#include <iostream>  // std::cout/endl
#include <utility>   // std::move

using namespace std;

class Obj {
public:
    Obj()
    {
        cout << "Obj()" << endl;
    }
    Obj(const Obj&)
    {
        cout << "Obj(const Obj&)" << endl;
    }
    Obj(Obj&&)
    {
        cout << "Obj(Obj&&)" << endl;
    }
};

Obj simple()
{
    Obj obj;
    return obj;
}

Obj simple_with_move()
{
    Obj obj;
    return std::move(obj);
}

Obj complicated(int n)
{
    Obj obj1;
    Obj obj2;
    if (n % 2 == 0) {
        return obj1;
    } else {
        return obj2;
    }
}

int main()
{
    cout << "*** 1 ***" << endl;
    auto obj1 = simple();
    cout << "*** 2 ***" << endl;
    auto obj2 = simple_with_move();
    cout << "*** 3 ***" << endl;
    auto obj3 = complicated(42);
}
