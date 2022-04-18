#include <stdio.h>           // printf
#include "memory_context.h"  // MEMORY_CHECKPOINT

int main()
{
    MEMORY_CHECKPOINT();
    auto ptr = new char[20];
    printf("Allocated pointer: %p\n", ptr);
    ptr[-1] = 0;
    ptr[-5] = 0;
}

