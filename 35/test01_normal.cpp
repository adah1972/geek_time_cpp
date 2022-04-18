#include "memory_context.h"  // MEMORY_CHECKPOINT

int main()
{
    MEMORY_CHECKPOINT();
    auto ptr = new char[20];
    delete[] ptr;
}
