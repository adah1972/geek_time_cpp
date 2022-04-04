#include <thread>               // std::thread
#include <unordered_set>        // std::unordered_set
#include "container_op_test.h"  // test_container
#include "pooled_allocator.h"   // pooled_allocator

using namespace std;

namespace {
#if defined(_GLIBCXX_UNORDERED_SET)
thread_local auto& pool_decl_ref =
    get_memory_pool<std::__detail::_Hash_node<int, false>>();
#elif defined(_LIBCPP_UNORDERED_SET)
thread_local auto& pool_decl_ref =
    get_memory_pool<std::__1::__hash_node<int, void*>>();
#elif defined(_MSC_VER)
thread_local auto& pool_decl_ref =
    get_memory_pool<std::_List_node<int, void*>>();
#else
#error "I do not know how to declare the memory pool for your environment!"
#endif
}  // unnamed namespace

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
