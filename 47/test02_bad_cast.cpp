#include <stdio.h>

int foo(int* p1, float* p2)
{
    *p1 = 1;
    *p2 = 3.0;
    return *p1;
}

int main()
{
    int n = 0;
    printf("%x\n", foo(&n, (float*)&n));
}
