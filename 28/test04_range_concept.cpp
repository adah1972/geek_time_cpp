#include <iostream>                      // std::cout/endl
#include <string>                        // std::string
#include <type_traits>                   // std::decay_t
#include <vector>                        // std::vector
#include "output_container.h"            // operator<< for containers

using namespace std;

#if defined(__cpp_concepts)

#if __cpp_concepts < 201811 || !__has_include(<ranges>)

#include <experimental/ranges/concepts>  // concepts defined in ranges
using namespace experimental::ranges;

#else

#include <ranges>                        // std::ranges::range
using namespace ranges;

#endif

#define REQUIRES(x) requires x

#else // defined(__cpp_concepts)

#define REQUIRES(x)

#endif

template <template <typename, typename> class OutContainer = vector,
          typename F, class R>
    requires range<R>
auto fmap(F&& f, R&& inputs)
{
    typedef decay_t<decltype(f(*inputs.begin()))> result_type;
    OutContainer<result_type, allocator<result_type>> result;
    for (auto&& item : inputs) {
        result.push_back(f(item));
    }
    return result;
}

int main()
{
    vector<string> v{"Hello", "World"};
    cout << v << endl;
    auto result = fmap([](auto&& s) { return s.size(); }, v);
    cout << result << endl;
}
