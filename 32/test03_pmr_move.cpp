#include <iostream>         // std::cout/endl
#include <memory_resource>  // std::pmr::...
#include <new>              // operator new/delete
#include <vector>           // std::vector

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

struct Obj {
    Obj() = default;
    Obj(const Obj&) { ++s_copy_count; }
    Obj(Obj&&) noexcept { ++s_move_count; }
    Obj& operator=(const Obj&)
    {
        ++s_copy_count;
        return *this;
    }
    Obj& operator=(Obj&&) noexcept
    {
        ++s_move_count;
        return *this;
    }
    ~Obj() = default;

    static void ShowStats()
    {
        cout << "Copy count: " << s_copy_count << endl;
        cout << "Move count: " << s_move_count << endl;
    }

private:
    static int s_copy_count;
    static int s_move_count;
};

int Obj::s_copy_count;
int Obj::s_move_count;

int main()
{
    new_delete_alloc_resource res;
    std::pmr::polymorphic_allocator<int> a(&res);

    pmr::vector<Obj> v1;
    v1.emplace_back();
    v1.emplace_back();
    v1.emplace_back();

    pmr::vector<Obj> v2;
    cout << "Before moving vector<Obj> of same allocator" << endl;
    Obj::ShowStats();

    v2 = std::move(v1);
    cout << "\n*After moving vector<Obj> of same allocator" << endl;
    Obj::ShowStats();

    pmr::vector<Obj> v3(a);
    v3 = std::move(v2);
    cout << "\n*After moving vector<Obj> of different allocators" << endl;
    Obj::ShowStats();
}
