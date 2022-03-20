#include <stdio.h>   // printf
#include <string.h>  // memset
#include <time.h>    // clock

int main()
{
    constexpr int LOOPS = 10000000;
    char buf[80];
    clock_t t1;
    clock_t t2;

    t1 = clock();
    for (int i = 0; i < LOOPS; ++i) {
        memset(buf, 0, sizeof buf);
    }
    t2 = clock();
    printf("%g\n", (t2 - t1) * 1.0 / CLOCKS_PER_SEC);

    t1 = clock();
    for (int i = 0; i < LOOPS; ++i) {
        for (size_t j = 0; j < sizeof buf; ++j) {
            buf[j] = 0;
        }
    }
    t2 = clock();
    printf("%g\n", (t2 - t1) * 1.0 / CLOCKS_PER_SEC);
}
