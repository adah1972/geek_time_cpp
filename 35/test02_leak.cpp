#include "memory_context.h"  // MEMORY_CHECKPOINT

int main()
{
    auto ptr1 = new char[10];
    MEMORY_CHECKPOINT();
    auto ptr2 = new char[20];
}
