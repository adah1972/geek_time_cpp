#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <array>    // std::array
#include <cassert>  // assert
#include <cstddef>  // std::size_t
#include <cstdint>  // std::uintptr_t

template <typename T>
inline constexpr std::size_t memory_chunk_size = 64;

template <typename T>
class memory_chunk {
public:
    union node {
        T data;
        node* next;
        node() {}
        ~node() {}
        node(const node&) = delete;
        node& operator=(const node&) = delete;
    };
    memory_chunk(memory_chunk* next_chunk);
    node* get_free_nodes() { return storage_.data(); }
    memory_chunk* get_next() { return next_chunk_; }

private:
    memory_chunk* next_chunk_{};
    std::array<node, memory_chunk_size<T>> storage_;
};

template <typename T>
memory_chunk<T>::memory_chunk(memory_chunk* next_chunk)
    : next_chunk_(next_chunk)
{
    for (std::size_t i = 0; i < storage_.size() - 1; ++i) {
        storage_[i].next = &storage_[i + 1];
    }
    storage_[storage_.size() - 1].next = nullptr;
}

template <typename T>
class memory_pool {
public:
    using node = typename memory_chunk<T>::node;

    memory_pool() = default;
    memory_pool(const memory_pool&) = delete;
    memory_pool& operator=(const memory_pool&) = delete;
    ~memory_pool();
    T* allocate();
    void deallocate(T* ptr);

private:
    node* free_list_{};
    memory_chunk<T>* chunk_list_{};
};

template <typename T>
memory_pool<T>::~memory_pool()
{
    while (chunk_list_) {
        memory_chunk<T>* chunk = chunk_list_;
        chunk_list_ = chunk_list_->get_next();
        delete chunk;
    }
}

template <typename T>
T* memory_pool<T>::allocate()
{
    if (free_list_ == nullptr) {
        chunk_list_ = new memory_chunk<T>(chunk_list_);
        free_list_ = chunk_list_->get_free_nodes();
    }

    T* result = &free_list_->data;
    assert(reinterpret_cast<std::uintptr_t>(result) % sizeof(T*) == 0);
    free_list_ = free_list_->next;
    return result;
}

template <typename T>
void memory_pool<T>::deallocate(T* ptr)
{
    assert(reinterpret_cast<std::uintptr_t>(ptr) % sizeof(T*) == 0);
    auto free_item = reinterpret_cast<node*>(ptr);
    free_item->next = free_list_;
    free_list_ = free_item;
}

#endif // MEMORY_POOL_H
