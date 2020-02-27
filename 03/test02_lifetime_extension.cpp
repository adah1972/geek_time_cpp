#include <stdio.h>  // puts
#include "shape.h"  // shape/circle/triangle

class result {
public:
    result() { puts("result()"); }
    ~result() { puts("~result()"); }
};

result process_shape(const shape& shape1, const shape& shape2)
{
    puts("process_shape()");
    return result();
}

int main()
{
    puts("main()");
    result&& r = process_shape(circle(), triangle());
    puts("something else");
}
