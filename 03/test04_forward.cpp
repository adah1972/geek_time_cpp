#include <utility>  // std::forward
#include <stdio.h>  // puts

class shape {
public:
    virtual ~shape() {}
};

class circle : public shape {
public:
    circle() {}
    ~circle() {}
};

void foo(const shape&)
{
    puts("foo(const shape&)");
}

void foo(shape&&)
{
    puts("foo(shape&&)");
}

template <typename T>
void bar(T&& s)
{
    foo(std::forward<T>(s));
}

int main()
{
    circle temp;
    bar(temp);
    bar(circle());
}
