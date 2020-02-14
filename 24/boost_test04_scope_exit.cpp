#include <stdio.h>
#include <boost/scope_exit.hpp>

void test()
{
    FILE* fp = fopen("../boost_test04_scope_exit.cpp", "r");
    if (fp == NULL) {
        perror("Cannot open file");
    }
    BOOST_SCOPE_EXIT(&fp)
    {
        if (fp) {
            fclose(fp);
            puts("File is closed");
        }
    }
    BOOST_SCOPE_EXIT_END
    puts("Faking an exception");
    throw 42;
}

int main()
{
    try {
        test();
    }
    catch (int) {
        puts("Exception received");
    }
}
