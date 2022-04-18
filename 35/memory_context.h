#ifndef MEMORY_CONTEXT_H
#define MEMORY_CONTEXT_H

#include <cstddef>  // std::size_t
#include <new>      // std::align_val_t

int check_leaks();

struct context {
    const char* file;
    const char* func;
};

class checkpoint {
public:
    explicit checkpoint(const context& ctx);
    ~checkpoint();
    checkpoint(const checkpoint&) = delete;
    checkpoint& operator=(const checkpoint&) = delete;
};

#ifdef __GNUC__

#define MEMORY_CHECKPOINT()                        \
    checkpoint func_checkpoint                     \
    {                                              \
        context { __FILE__, __PRETTY_FUNCTION__ }  \
    }

#else

#define MEMORY_CHECKPOINT()                        \
    checkpoint func_checkpoint                     \
    {                                              \
        context { __FILE__, __func__ }             \
    }

#endif

void* operator new  (std::size_t size, const context& ctx);
void* operator new[](std::size_t size, const context& ctx);
void* operator new  (std::size_t size, std::align_val_t align_val,
                     const context& ctx);
void* operator new[](std::size_t size, std::align_val_t align_val,
                     const context& ctx);

void operator delete  (void* ptr, const context&) noexcept;
void operator delete[](void* ptr, const context&) noexcept;
void operator delete  (void* ptr, std::align_val_t align_val,
                       const context&) noexcept;
void operator delete[](void* ptr, std::align_val_t align_val,
                       const context&) noexcept;

#endif // MEMORY_CONTEXT_H
