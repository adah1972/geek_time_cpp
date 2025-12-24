#ifndef CONTAINER_OP_TEST_H
#define CONTAINER_OP_TEST_H

#include <algorithm>  // std::shuffle
#include <array>      // std::array
#include <cstddef>    // std::size_t
#include <cstdint>    // std::uint64_t
#include <iomanip>    // std::setw
#include <iostream>   // std::cout
#include <random>     // std::mt19937/uniform_int_distribution
#include "rdtsc.h"    // rdtsc

#define LEN 5000

template <typename T>
void test_container(T& obj)
{
    using namespace std;

    uint64_t t1{};
    uint64_t t2{};

    mt19937 engine;
    uniform_int_distribution<int> dist;
    array<int, LEN> rand_nums{};
    for (int& num : rand_nums) {
        num = dist(engine);
    }

    t1 = rdtsc();
    for (int num : rand_nums) {
        obj.insert(num);
    }
    t2 = rdtsc();
    cout << "It took " << setw(3) << (t2 - t1) / LEN
         << " cycles by average to insert a number\n";

    shuffle(begin(rand_nums), end(rand_nums), engine);

    t1 = rdtsc();
    for (int num : rand_nums) {
        obj.erase(num);
    }
    t2 = rdtsc();
    cout << "It took " << setw(3) << (t2 - t1) / LEN
         << " cycles by average to erase  a number\n";

    shuffle(begin(rand_nums), end(rand_nums), engine);

    t1 = rdtsc();
    for (int num : rand_nums) {
        obj.insert(num);
    }
    t2 = rdtsc();
    cout << "It took " << setw(3) << (t2 - t1) / LEN
         << " cycles by average to insert a number again\n";
}

#endif // CONTAINER_OP_TEST_H
