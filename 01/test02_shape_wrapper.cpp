#include "shape.h"  // shape/shape_type/create_shape

class shape_wrapper {
public:
    explicit shape_wrapper(shape* ptr = nullptr)
        : ptr_(ptr) {}
    ~shape_wrapper()
    {
        delete ptr_;
    }
    shape* get() const { return ptr_; }

private:
    shape* ptr_;
};

void foo()
{
    shape_wrapper ptr_wrapper(create_shape(shape_type::circle));
}

int main()
{
    foo();
}
