#if __has_include(<memory_resource>)

#include <memory_resource>      // std::pmr::...
#include <thread>               // std::thread
#include <unordered_set>        // std::unordered_set
#include "container_op_test.h"  // test_container

using namespace std;

using TestType = pmr::unordered_set<int>;
pmr::unsynchronized_pool_resource res;
pmr::polymorphic_allocator<int> a{&res};

int main()
{
    // Linux shows a performance difference, depending on whether there
    // have been more than one thread.
    thread t{[] {}};
    t.join();

    TestType s(a);
    test_container(s);
}

#else

#include <iostream>  // std::cerr

int main()
{
    std::cerr << "This test does nothing, as your compiler does not "
                 "support <memory_resource>!\n";
}

#endif
