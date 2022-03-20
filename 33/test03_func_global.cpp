#include <mutex>     // std::mutex/lock_guard
#include <stdio.h>   // printf
#include <string.h>  // memset
#include "rdtsc.h"   // rdtsc

char buf[80];
uint64_t memset_duration;
uint64_t plain_loop_duration;
std::mutex mutex;

void test_memset()
{
    uint64_t t1 = rdtsc();
    memset(buf, 0, sizeof buf);
    uint64_t t2 = rdtsc();
    memset_duration += (t2 - t1);
}

void test_plain_loop()
{
    uint64_t t1 = rdtsc();
    for (size_t j = 0; j < sizeof buf; ++j) {
        buf[j] = 0;
    }
    uint64_t t2 = rdtsc();
    plain_loop_duration += (t2 - t1);
}

int main()
{
    constexpr int LOOPS = 10000000;

    for (int i = 0; i < LOOPS; ++i) {
        std::lock_guard guard{mutex};
        test_memset();
    }
    printf("%g\n", memset_duration * 1.0 / LOOPS);

    for (int i = 0; i < LOOPS; ++i) {
        std::lock_guard guard{mutex};
        test_plain_loop();
    }
    printf("%g\n", plain_loop_duration * 1.0 / LOOPS);
}
