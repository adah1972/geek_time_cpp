#include <thread>               // std::thread
#include <unordered_set>        // std::unordered_set
#include "container_op_test.h"  // test_container
#include "pooled_allocator.h"   // pooled_allocator

using namespace std;

using TestType =
    unordered_set<int, hash<int>, equal_to<int>, pooled_allocator<int>>;
thread_local TestType s;

int main()
{
    // Linux shows a performance difference, depending on whether there
    // have been more than one thread.
    thread t{[] {}};
    t.join();

    test_container(s);
}
