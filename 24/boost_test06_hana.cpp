#include <boost/hana.hpp>  // boost::hana
namespace hana = boost::hana;

class shape {};
class circle {};
class triangle {};

int main()
{
    using namespace hana::literals;

    constexpr auto tup = hana::make_tuple(
        hana::type_c<shape*>, hana::type_c<circle>, hana::type_c<triangle>);

    constexpr auto no_pointers = hana::remove_if(
        tup, [](auto a) { return hana::traits::is_pointer(a); });

    static_assert(no_pointers == hana::make_tuple(hana::type_c<circle>,
                                                  hana::type_c<triangle>));
    static_assert(
        hana::reverse(no_pointers) ==
        hana::make_tuple(hana::type_c<triangle>, hana::type_c<circle>));
    static_assert(tup[1_c] == hana::type_c<circle>);
}
