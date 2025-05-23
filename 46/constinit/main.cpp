#include <stdio.h>   // printf/putchar
#include "primes.h"  // primes_data/primes_size

int main()
{
    for (auto* p = primes_data; p != primes_data + primes_size; ++p) {
        printf("%d ", *p);
    }
    putchar('\n');
}
