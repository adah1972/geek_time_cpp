#include <iostream>              // std::cout
#include <ranges>                // std::views::reverse
#include <vector>                // std::vector
#include <boost/type_index.hpp>  // boost::typeindex::type_id_with_cvr

using namespace std;
using boost::typeindex::type_id_with_cvr;

int main()
{
    vector v{1, 2, 3, 4, 5};
    auto vw1 = v | views::reverse;
    cout << type_id_with_cvr<decltype(vw1)>().pretty_name() << '\n';
#if __cpp_lib_ranges >= 202110L
    auto vw2 = vector{1, 2, 3, 4, 5} | views::reverse;
    cout << type_id_with_cvr<decltype(vw2)>().pretty_name() << '\n';
#endif
}
