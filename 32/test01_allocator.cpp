#include <cstddef>      // std::size_t/ptrdiff_t
#include <iostream>     // std::cout/endl
#include <new>          // operator new
#include <type_traits>  // type traits
#include <utility>      // std::forward
#include <vector>       // std::vector

using namespace std;

template <class T>
class verbose_alloc {
public:
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using value_type = T;
    using propagate_on_container_move_assignment = true_type;
    using is_always_equal = true_type;

    template <class U>
    struct rebind {
        using other = verbose_alloc<U>;
    };

    verbose_alloc() = default;

    template <class U>
    verbose_alloc(const verbose_alloc<U>&) noexcept
    {
    }

    T* allocate(size_t n)
    {
        cout << "Allocating " << n << " objects of size " << sizeof(T)
             << endl;
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, size_t n) noexcept
    {
        cout << "Deallocating " << n << " objects of size " << sizeof(T)
             << endl;
        ::operator delete(p);
    }

    template <typename U, typename... Args>
    void construct(U* p, Args&&... args) noexcept(
        is_nothrow_constructible_v<U, Args...>)
    {
#if defined(__GNUC__)
        cout << __PRETTY_FUNCTION__ << endl;
#elif defined(_MSC_VER)
        cout << __FUNCSIG__ << endl;
#endif
        ::new((void*)p) U(forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U* p) noexcept(is_nothrow_destructible_v<U>)
    {
#if defined(__GNUC__)
        cout << __PRETTY_FUNCTION__ << endl;
#elif defined(_MSC_VER)
        cout << __FUNCSIG__ << endl;
#endif
        p->~U();
    }
};

template <class T>
constexpr bool operator==(const verbose_alloc<T>&, const verbose_alloc<T>&)
{
    return true;
}

template <class T>
constexpr bool operator!=(const verbose_alloc<T>&, const verbose_alloc<T>&)
{
    return false;
}

int main()
{
    cout << "*** Entering main" << endl;
    vector<int, verbose_alloc<int>> v{1, 2, 3, 4, 5};
    cout << "*** Exiting main" << endl;
}
