#include <stdio.h>  // printf/putchar

template <typename T>
void dump(const T& str)
{
    for (char ch : str) {
        printf("%.2x ", static_cast<unsigned char>(ch));
    }
    putchar('\n');
}

int main()
{
    char str[] = "你好";
    char u8str[] = u8"你好";
    dump(str);
    dump(u8str);
}
