#ifndef SMART_PTR_H
#define SMART_PTR_H

#include <atomic>     // std::atomic
#include <utility>    // std::swap
#include "finally.h"  // finally

class shared_count {
public:
    shared_count() noexcept : count_(1) {}
    void add_count() noexcept
    {
        count_.fetch_add(1, std::memory_order_relaxed);
    }
    long reduce_count() noexcept
    {
        return --count_;
    }
    long get_count() const noexcept
    {
        return count_;
    }

private:
    std::atomic_long count_;
};

template <typename T>
class smart_ptr {
public:
    template <typename U>
    friend class smart_ptr;

    explicit smart_ptr(T* ptr = nullptr) : ptr_(ptr)
    {
        if (ptr) {
            auto release_ptr_action = finally([ptr] { delete ptr; });
            shared_count_ = new shared_count();
            release_ptr_action.dismiss();
        }
    }
    ~smart_ptr()
    {
        if (ptr_ && !shared_count_->reduce_count()) {
            delete ptr_;
            delete shared_count_;
        }
    }

    smart_ptr(const smart_ptr& other) noexcept : ptr_(other.ptr_)
    {
        if (ptr_) {
            other.shared_count_->add_count();
            shared_count_ = other.shared_count_;
        }
    }
    template <typename U>
    smart_ptr(const smart_ptr<U>& other) noexcept : ptr_(other.ptr_)
    {
        if (ptr_) {
            other.shared_count_->add_count();
            shared_count_ = other.shared_count_;
        }
    }
    template <typename U>
    smart_ptr(smart_ptr<U>&& other) noexcept : ptr_(other.ptr_)  // NOLINT
    {
        if (ptr_) {
            shared_count_ = other.shared_count_;
            other.ptr_ = nullptr;
        }
    }
    template <typename U>
    smart_ptr(const smart_ptr<U>& other, T* ptr) noexcept : ptr_(ptr)
    {
        if (ptr_) {
            other.shared_count_->add_count();
            shared_count_ = other.shared_count_;
        }
    }
    smart_ptr& operator=(smart_ptr rhs) noexcept
    {
        rhs.swap(*this);
        return *this;
    }

    T* get() const noexcept
    {
        return ptr_;
    }
    long use_count() const noexcept
    {
        if (ptr_) {
            return shared_count_->get_count();
        } else {
            return 0;
        }
    }
    void swap(smart_ptr& rhs) noexcept
    {
        using std::swap;
        swap(ptr_, rhs.ptr_);
        swap(shared_count_, rhs.shared_count_);
    }

    T& operator*() const noexcept
    {
        return *ptr_;
    }
    T* operator->() const noexcept
    {
        return ptr_;
    }
    operator bool() const noexcept
    {
        return ptr_;
    }

private:
    T* ptr_;
    shared_count* shared_count_;
};

template <typename T>
void swap(smart_ptr<T>& lhs, smart_ptr<T>& rhs) noexcept
{
    lhs.swap(rhs);
}

template <typename T, typename U>
smart_ptr<T> static_pointer_cast(const smart_ptr<U>& other) noexcept
{
    T* ptr = static_cast<T*>(other.get());
    return smart_ptr<T>(other, ptr);
}

template <typename T, typename U>
smart_ptr<T> reinterpret_pointer_cast(const smart_ptr<U>& other) noexcept
{
    T* ptr = reinterpret_cast<T*>(other.get());
    return smart_ptr<T>(other, ptr);
}

template <typename T, typename U>
smart_ptr<T> const_pointer_cast(const smart_ptr<U>& other) noexcept
{
    T* ptr = const_cast<T*>(other.get());
    return smart_ptr<T>(other, ptr);
}

template <typename T, typename U>
smart_ptr<T> dynamic_pointer_cast(const smart_ptr<U>& other) noexcept
{
    T* ptr = dynamic_cast<T*>(other.get());
    return smart_ptr<T>(other, ptr);
}

#endif // SMART_PTR_H
