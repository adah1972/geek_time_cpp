#include <iostream>            // std::cout/endl
#include <memory_resource>     // std::pmr::...
#include <new>                 // operator new/delete
#include <vector>              // std::vector
#include "output_container.h"  // operator<< for containers

using namespace std;

class new_delete_alloc_resource : public pmr::memory_resource {
public:
    void* do_allocate(size_t bytes, size_t alignment) override
    {
        return ::operator new(bytes, align_val_t{alignment});
    }

    void do_deallocate(void* p, size_t bytes, size_t alignment) override
    {
        ::operator delete(p, align_val_t{alignment});
    }

    bool
    do_is_equal(const pmr::memory_resource& other) const noexcept override
    {
        return dynamic_cast<const new_delete_alloc_resource*>(&other);
    }
};

int main()
{
    vector<int, pmr::polymorphic_allocator<int>> v1{1, 2, 3};
    new_delete_alloc_resource res;
    pmr::set_default_resource(&res);
    vector<int, pmr::polymorphic_allocator<int>> v2;
    v2 = v1;
    cout << "v1: " << v1 << endl;
    cout << "v2: " << v2 << endl;
    cout << "v1 and v2 have "
         << (v2.get_allocator() == v1.get_allocator() ? "SAME"
                                                      : "DIFFERENT")
         << " allocators" << endl;
}
