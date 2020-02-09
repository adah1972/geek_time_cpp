#include <string>
#include <vector>

using namespace std;

#if defined(__cpp_concepts)

#if __cpp_concepts < 201811

#include <experimental/ranges/concepts>
using namespace experimental::ranges;

#else

#include <concepts>
using namespace ranges;

#endif

#define REQUIRES(x) requires x

#else // defined(__cpp_concepts)

#define REQUIRES(x)

#endif

template <typename R, typename T>
    REQUIRES((range<R> &&
              equality_comparable_with<T, typename R::value_type>))
bool in(R const& r, T const& value)
{
    for (auto const& x : r)
        if (x == value)
            return true;
    return false;
}

int main()
{
    vector<string> v{"Hello", "World"};
    in(v, "Hello");
    // Uncomment the following line to see errors
    // in(v, 0);
}
