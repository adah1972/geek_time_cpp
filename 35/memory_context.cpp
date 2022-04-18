#include "memory_context.h"  // context/checkpoint
#include <cstddef>           // std::size_t/byte
#include <cstdio>            // std::printf/puts
#include <cstdlib>           // std::abort
#include <new>               // placement new
#include <stack>             // std::stack

#ifdef _WIN32
#include <malloc.h>
#endif

using namespace std;

const context default_ctx{"<UNKNOWN>", "<UNKNOWN>"};

template <typename T>
struct malloc_allocator {
    typedef T value_type;
    typedef std::true_type is_always_equal;
    typedef std::true_type propagate_on_container_move_assignment;

    malloc_allocator() = default;
    template <typename U>
    malloc_allocator(const malloc_allocator<U>&)
    {}

    template <typename U>
    struct rebind {
        typedef malloc_allocator<U> other;
    };

    T* allocate(size_t n) { return static_cast<T*>(malloc(n * sizeof(T))); }
    void deallocate(T* p, size_t) { free(p); }
};

thread_local stack<context, deque<context, malloc_allocator<context>>>
    context_stack;

const context& get_current_context()
{
    if (context_stack.empty()) {
        return default_ctx;
    }
    return context_stack.top();
}

void save_context(const context& ctx)
{
    context_stack.push(ctx);
}

void restore_context()
{
    context_stack.pop();
}

checkpoint::checkpoint(const context& ctx)
{
    save_context(ctx);
}

checkpoint::~checkpoint()
{
    restore_context();
}

constexpr uint32_t MAGIC = 0x4D'58'54'43;  // "CTXM";

size_t current_mem_alloc = 0;

struct alloc_list_base {
    alloc_list_base* next;
    alloc_list_base* prev;
};

struct alloc_list_t : alloc_list_base {
    size_t size;
    context ctx;
    uint32_t head_size;
    uint32_t magic;
};

alloc_list_base alloc_list = {
    &alloc_list,  // head (next)
    &alloc_list,  // tail (prev)
};

constexpr uint32_t align(size_t alignment, size_t s)
{
    return static_cast<uint32_t>((s + alignment - 1) & ~(alignment - 1));
}

alloc_list_t* convert_user_ptr(void* usr_ptr, size_t alignment)
{
    auto offset = static_cast<byte*>(usr_ptr) - static_cast<byte*>(nullptr);
    auto byte_ptr = static_cast<byte*>(usr_ptr);

    if (offset % alignment != 0) {
        return nullptr;
    }
    auto ptr = reinterpret_cast<alloc_list_t*>(
        byte_ptr - align(alignment, sizeof(alloc_list_t)));
    if (ptr->magic != MAGIC) {
        return nullptr;
    }

    return ptr;
}

void* alloc_mem(size_t size, const context& ctx,
                size_t alignment = __STDCPP_DEFAULT_NEW_ALIGNMENT__)
{
    uint32_t aligned_list_node_size =
        align(alignment, sizeof(alloc_list_t));
    size_t s = size + aligned_list_node_size;
#ifdef _WIN32
    auto ptr = static_cast<alloc_list_t*>(
        _aligned_malloc(s, alignment));
#else
    auto ptr = static_cast<alloc_list_t*>(
        aligned_alloc(alignment, align(alignment, s)));
#endif
    if (ptr == nullptr) {
        return nullptr;
    }
    auto usr_ptr = reinterpret_cast<byte*>(ptr) + aligned_list_node_size;
    ptr->ctx = ctx;
    ptr->size = size;
    ptr->head_size = aligned_list_node_size;
    ptr->magic = MAGIC;
    ptr->prev = alloc_list.prev;
    ptr->next = &alloc_list;
    alloc_list.prev->next = ptr;
    alloc_list.prev = ptr;
    current_mem_alloc += size;
    return usr_ptr;
}

void free_mem(void* usr_ptr,
              size_t alignment = __STDCPP_DEFAULT_NEW_ALIGNMENT__)
{
    if (usr_ptr == nullptr) {
        return;
    }

    auto ptr = convert_user_ptr(usr_ptr, alignment);
    if (ptr == nullptr) {
        puts("Invalid pointer or double-free");
        abort();
    }
    current_mem_alloc -= ptr->size;
    ptr->magic = 0;
    ptr->prev->next = ptr->next;
    ptr->next->prev = ptr->prev;
#ifdef _WIN32
    _aligned_free(ptr);
#else
    free(ptr);
#endif
}

void* operator new(size_t size, const context& ctx)
{
    void* ptr = alloc_mem(size, ctx);
    if (ptr) {
        return ptr;
    } else {
        throw bad_alloc();
    }
}

void* operator new[](size_t size, const context& ctx)
{
    void* ptr = alloc_mem(size, ctx);
    if (ptr) {
        return ptr;
    } else {
        throw bad_alloc();
    }
}

void* operator new(size_t size, align_val_t align_val, const context& ctx)
{
    void* ptr = alloc_mem(size, ctx, size_t(align_val));
    if (ptr) {
        return ptr;
    } else {
        throw bad_alloc();
    }
}

void* operator new[](size_t size, align_val_t align_val, const context& ctx)
{
    void* ptr = alloc_mem(size, ctx, size_t(align_val));
    if (ptr) {
        return ptr;
    } else {
        throw bad_alloc();
    }
}

void operator delete(void* ptr, const context&) noexcept
{
    free_mem(ptr);
}

void operator delete[](void* ptr, const context&) noexcept
{
    free_mem(ptr);
}
void operator delete(void* ptr, align_val_t align_val,
                     const context&) noexcept
{
    free_mem(ptr, size_t(align_val));
}
void operator delete[](void* ptr, align_val_t align_val,
                       const context&) noexcept
{
    free_mem(ptr, size_t(align_val));
}

void* operator new(size_t size)
{
    return operator new(size, get_current_context());
}
void* operator new[](size_t size)
{
    return operator new[](size, get_current_context());
}

void operator delete(void* ptr) noexcept
{
    free_mem(ptr);
}
void operator delete[](void* ptr) noexcept
{
    free_mem(ptr);
}

int check_leaks()
{
    int leak_cnt = 0;
    auto ptr = static_cast<alloc_list_t*>(alloc_list.next);

    while (ptr != &alloc_list) {
        if (ptr->magic != MAGIC) {
            printf("error: heap data corrupt near %p\n", &ptr->magic);
            abort();
        }

        auto usr_ptr = reinterpret_cast<const byte*>(ptr) + ptr->head_size;
        printf("Leaked object at %p (size %zu, ", usr_ptr, ptr->size);
        printf("context: %s/%s)\n", ptr->ctx.file, ptr->ctx.func);

        ptr = static_cast<alloc_list_t*>(ptr->next);
        ++leak_cnt;
    }
    if (leak_cnt) {
        printf("*** %d leaks found\n", leak_cnt);
    }

    return leak_cnt;
}

class invoke_check_leak_t {
public:
    ~invoke_check_leak_t() { check_leaks(); }
} invoke_check_leak;
