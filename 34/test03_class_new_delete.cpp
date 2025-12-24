#include <array>          // std::array
#include <cassert>        // assert
#include <cstddef>        // std::size_t
#include <cstdint>        // std::uint64_t
#include <iomanip>        // std::setw
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include "memory_pool.h"  // memory_pool
#include "rdtsc.h"        // rdtsc

using namespace std;

namespace normal {
class Obj {
public:
    Obj() {}
    ~Obj() {}
};
}  // namespace normal

namespace pooled {
class Obj {
public:
    Obj() {}
    ~Obj() {}
    void* operator new(size_t size);
    void operator delete(void* ptr) noexcept;
};

memory_pool<Obj> obj_pool;

void* Obj::operator new(size_t size)
{
    assert(size == sizeof(Obj));
    (void)size;
    return obj_pool.allocate();
}

void Obj::operator delete(void* ptr) noexcept
{
    obj_pool.deallocate(static_cast<Obj*>(ptr));
}
}  // namespace pooled

#define LEN 5000
#define LOOPS 1000

array<normal::Obj*, LEN> ptr_array1{};
array<pooled::Obj*, LEN> ptr_array2{};

int main()
{
    // Linux shows a performance difference, depending on whether there
    // have been more than one thread.
    thread t{[] {}};
    t.join();

    uint64_t t1{};
    uint64_t t2{};

    t1 = rdtsc();
    for (int i = 0; i < LOOPS; ++i) {
        for (auto& ptr : ptr_array1) {
            ptr = new normal::Obj;
        }
        for (auto ptr : ptr_array1) {
            delete ptr;
        }
    }
    t2 = rdtsc();
    cout << setw(3) << (t2 - t1) / LOOPS / LEN
         << " cycles for each allocation and deallocations on normal Obj\n";

    t1 = rdtsc();
    for (int i = 0; i < LOOPS; ++i) {
        for (auto& ptr : ptr_array2) {
            ptr = new pooled::Obj;
        }
        for (auto ptr : ptr_array2) {
            delete ptr;
        }
    }
    t2 = rdtsc();
    cout << setw(3) << (t2 - t1) / LOOPS / LEN
         << " cycles for each allocation and deallocations on pooled Obj\n";
}
