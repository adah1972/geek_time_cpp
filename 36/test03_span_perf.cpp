#include <algorithm>      // std::copy
#include <cassert>        // assert
#include <iostream>       // std::cout
#include <mutex>          // std::mutex/lock_guard
#include <random>         // std::mt19937/uniform_int_distribution
#include <vector>         // std::vector
#include <gsl/algorithm>  // gsl::copy
#include <gsl/span>       // gsl::span
#include "profiler.h"     // PROFILE_CHECK

#ifndef HAS_STD_SPAN
#if __cplusplus > 201703L && __has_include(<span>)
#define HAS_STD_SPAN 1
#include <span>           // std::span
#else
#define HAS_STD_SPAN 0
#endif
#endif

enum profiled_functions {
    PF_COPY_DIRECT,
#if HAS_STD_SPAN
    PF_COPY_STD_SPAN,
#endif
    PF_COPY_GSL_SPAN,
    PF_GSL_COPY_SPAN,
};

name_mapper name_map[] = {
    {PF_COPY_DIRECT, "copy_direct"},
#if HAS_STD_SPAN
    {PF_COPY_STD_SPAN, "copy_std_span"},
#endif
    {PF_COPY_GSL_SPAN, "copy_gsl_span"},
    {PF_GSL_COPY_SPAN, "gsl_copy_span"},
    {-1, nullptr}};

#define LEN   1000
#define LOOPS 1000

std::vector<int> src;
std::vector<int> dest;
std::mutex mutex;

void init_src()
{
    std::mt19937 engine;
    std::uniform_int_distribution<int> dist;
    src.clear();
    for (int i = 0; i < LEN; ++i) {
        src.push_back(dist(engine));
    }
}

void reset_dest()
{
    dest.resize(0);
    dest.resize(src.size());
}

void copy_direct(const std::vector<int>& a, std::vector<int>& b)
{
    PROFILE_CHECK(PF_COPY_DIRECT);
    std::copy(a.begin(), a.end(), b.begin());
}

#if HAS_STD_SPAN
void copy_std_span(std::span<const int> a, std::span<int> b)
{
    PROFILE_CHECK(PF_COPY_STD_SPAN);
    std::copy(a.begin(), a.end(), b.begin());
}
#endif

void copy_gsl_span(gsl::span<const int> a, gsl::span<int> b)
{
    PROFILE_CHECK(PF_COPY_GSL_SPAN);
    std::copy(a.begin(), a.end(), b.begin());
}

void gsl_copy_span(gsl::span<const int> a, gsl::span<int> b)
{
    PROFILE_CHECK(PF_GSL_COPY_SPAN);
    gsl::copy(a, b);
}

int main()
{
    init_src();

    for (int i = 0; i < LOOPS; ++i) {
        {
            std::lock_guard guard{mutex};
            reset_dest();
            copy_direct(src, dest);
            assert(src[0] == dest[0] && src[1] == dest[1] &&
                   src[LEN - 1] == dest[LEN - 1]);
        }
#if HAS_STD_SPAN
        {
            std::lock_guard guard{mutex};
            reset_dest();
            copy_std_span(src, dest);
            assert(src[0] == dest[0] && src[1] == dest[1] &&
                   src[LEN - 1] == dest[LEN - 1]);
        }
#endif
        {
            std::lock_guard guard{mutex};
            reset_dest();
            copy_gsl_span(src, dest);
            assert(src[0] == dest[0] && src[1] == dest[1] &&
                   src[LEN - 1] == dest[LEN - 1]);
        }
        {
            std::lock_guard guard{mutex};
            reset_dest();
            gsl_copy_span(src, dest);
            assert(src[0] == dest[0] && src[1] == dest[1] &&
                   src[LEN - 1] == dest[LEN - 1]);
        }
    }
}
