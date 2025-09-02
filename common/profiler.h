#ifndef PROFILER_H
#define PROFILER_H

#include <stdint.h>  // uint64_t
#include "rdtsc.h"   // rdtsc

struct name_mapper {
    int number;
    const char* name;
};

extern name_mapper name_map[];

class profiling_checker {
public:
    profiling_checker(int number);
    ~profiling_checker();

#if __cplusplus >= 201103L
    profiling_checker(const profiling_checker&) = delete;
    profiling_checker& operator=(const profiling_checker&) = delete;
#endif

private:
    int number_;
    uint64_t start_time_;
};

inline profiling_checker::profiling_checker(int number)
    : number_(number), start_time_(rdtsc())
{
}

#ifdef NDEBUG
#define PROFILE_CHECK(func_number) (void)0
#else
#define PROFILE_CHECK(func_number) profiling_checker _checker(func_number)
#endif

#endif // PROFILER_H
