#include <ios>       // std::boolalpha
#include <iostream>  // std::cout/endl

using namespace std;

template <typename... Args>
constexpr bool is_any_null(const Args&... args)
{
    return (... || (args == nullptr));
}

int main()
{
    void* ptr = &cout;

    static_assert(is_any_null(nullptr));

    cout << boolalpha;
    cout << "ptr = " << ptr << endl;
    cout << "is_any_null(): " << is_any_null() << endl;
    cout << "is_any_null(ptr): " << is_any_null(ptr) << endl;
    cout << "is_any_null(ptr, nullptr): " << is_any_null(ptr, nullptr) << endl;
    cout << "is_any_null(nullptr, ptr): " << is_any_null(nullptr, ptr) << endl;
}
