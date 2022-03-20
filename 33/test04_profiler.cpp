#include <mutex>       // std::mutex/lock_guard
#include <stdio.h>     // printf
#include <string.h>    // memset
#include "profiler.h"  // PROFILE_CHECK

enum profiled_functions {
    PF_TEST_MEMSET,
    PF_TEST_PLAIN_LOOP,
};

name_mapper name_map[] = {
    {PF_TEST_MEMSET, "test_memset"},
    {PF_TEST_PLAIN_LOOP, "test_plain_loop"},
    {-1, nullptr}};

char buf[80];
std::mutex mutex;

void test_memset()
{
    PROFILE_CHECK(PF_TEST_MEMSET);
    memset(buf, 0, sizeof buf);
}

void test_plain_loop()
{
    PROFILE_CHECK(PF_TEST_PLAIN_LOOP);
    for (size_t j = 0; j < sizeof buf; ++j) {
        buf[j] = 0;
    }
}

int main()
{
    constexpr int LOOPS = 10000000;

    for (int i = 0; i < LOOPS; ++i) {
        std::lock_guard guard{mutex};
        test_memset();
    }

    for (int i = 0; i < LOOPS; ++i) {
        std::lock_guard guard{mutex};
        test_plain_loop();
    }
}
