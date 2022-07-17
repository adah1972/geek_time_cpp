#ifndef POOLED_ALLOCATOR_H
#define POOLED_ALLOCATOR_H

#include <memory>
#include "memory_pool.h"

template <typename T>
memory_pool<T>& get_memory_pool()
{
    thread_local memory_pool<T> pool;
    return pool;
}

template <typename T, typename Base = std::allocator<T>>
struct pooled_allocator : private Base {
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using value_type = T;

    using propagate_on_container_copy_assignment =
        typename std::allocator_traits<
            Base>::propagate_on_container_copy_assignment;
    using propagate_on_container_move_assignment =
        typename std::allocator_traits<
            Base>::propagate_on_container_move_assignment;
    using propagate_on_container_swap =
        typename std::allocator_traits<Base>::propagate_on_container_swap;
    using is_always_equal =
        typename std::allocator_traits<Base>::is_always_equal;

    template <class U>
    struct rebind {
        using other = pooled_allocator<U>;
    };

    pooled_allocator()
    {
        // Ensure the early creation of the memory pool.  Without this
        // call, a thread-local object may have lifetime issues using
        // this memory pool -- the memory pool may be destroyed earlier
        // than the object.  Also notice that a global/static object
        // generally cannot use this (thread-local) allocator safely.
        (void)get_memory_pool<T>();
    }

    template <class U>
    pooled_allocator(const pooled_allocator<U>&)
    {
    }

    T* allocate(std::size_t n)
    {
        if (n == 1) {
            return get_memory_pool<T>().allocate();
        } else {
            return Base::allocate(n);
        }
    }

    void deallocate(T* p, std::size_t n)
    {
        if (n == 1) {
            return get_memory_pool<T>().deallocate(p);
        } else {
            return Base::deallocate(p, n);
        }
    }
};

#endif // POOLED_ALLOCATOR_H
