#include <utility>  // std::swap/move
#include "shape.h"  // shape/shape_type/create_shape

template <typename T>
class smart_ptr {
public:
    explicit smart_ptr(T* ptr = nullptr)
        : ptr_(ptr) {}
    ~smart_ptr()
    {
        delete ptr_;
    }
    smart_ptr(smart_ptr&& other)
    {
        ptr_ = other.release();
    }
    smart_ptr& operator=(smart_ptr rhs)
    {
        rhs.swap(*this);
        return *this;
    }

    T* get() const { return ptr_; }
    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }
    operator bool() const { return ptr_; }
    T* release()
    {
        T* ptr = ptr_;
        ptr_ = nullptr;
        return ptr;
    }
    void swap(smart_ptr& rhs)
    {
        using std::swap;
        swap(ptr_, rhs.ptr_);
    }

private:
    T* ptr_;
};

int main()
{
    smart_ptr<shape> ptr1{create_shape(shape_type::circle)};
    //smart_ptr<shape> ptr2{ptr1};             // Cannot compile
    smart_ptr<shape> ptr3;
    //ptr3 = ptr1;                             // Cannot compile
    ptr3 = std::move(ptr1);                  // OK
    smart_ptr<shape> ptr4{std::move(ptr3)};  // OK
}
