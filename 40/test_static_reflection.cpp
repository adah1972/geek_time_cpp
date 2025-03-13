#include <cassert>                // assert
#include <ios>                    // std::boolalpha
#include <iostream>               // std::cout
#include <ostream>                // std::basic_ostream/ostream
#include <string>                 // std::string
#include <tuple>                  // std::tuple_element/tuple_size
#include <type_traits>            // std::decay_t
#include <typeinfo>               // std::type_info
#include "compile_time_string.h"  // CTS_GET_VALUE
#include "output_range.h"         // operator<< for tuples
#include "static_reflection.h"    // DEFINE_STRUCT/DECLARE_TUPLE_LIKE/sr::...

/* Outputs a "reflected" object */

class indent {
public:
    explicit indent(int n) : n_(n) {}
    template <typename CharT, typename Traits>
    friend std::basic_ostream<CharT, Traits>&
    operator<<(std::basic_ostream<CharT, Traits>& os, const indent& x)
    {
        for (int i = 0; i < x.n_; ++i) {
            os << "    ";
        }
        return os;
    }

private:
    int n_;
};

template <typename T>
void dump_obj(const T& obj, std::ostream& os = std::cout,
              const char* field_name = "", int depth = 0)
{
    if constexpr (sr::is_reflected_v<T>) {
        os << indent(depth) << field_name
           << (*field_name ? ": {\n" : "{\n");
        sr::for_each(obj, [depth, &os](auto field_name, const auto& value) {
            dump_obj(value, os, CTS_GET_VALUE(field_name), depth + 1);
        });
        os << indent(depth) << "}" << (depth == 0 ? "\n" : ",\n");
    } else {
        os << indent(depth) << field_name << ": ";
        output_range::output_element(os, obj, nullptr);  // os << obj;
        os << ",\n";
    }
}

/* Test structs */

namespace data {

using sr::get;  // NOLINT: Necessary for argument-dependent lookup

DEFINE_STRUCT(        //
    S1,               //
    (int)v1,          //
    (bool)v2,         //
    (std::string)msg  //
);

DEFINE_STRUCT(  //
    S2,         //
    (long)v1,   //
    (bool)v2    //
);

DEFINE_STRUCT(        //
    S3,               //
    (S2)values,       //
    (std::string)msg  //
);

DEFINE_STRUCT(           //
    S4,                  //
    (std::string)value1  //
);

DEFINE_STRUCT(           //
    S5,                  //
    (std::string)value2  //
);

// DECLARE_TUPLE_LIKE(S1); // won't compile

}  // namespace data

DECLARE_TUPLE_LIKE(data::S1);
DECLARE_TUPLE_LIKE(data::S2);
DECLARE_TUPLE_LIKE(data::S3);
DECLARE_TUPLE_LIKE(data::S4);
DECLARE_TUPLE_LIKE(data::S5);

/* Test code */

int main()
{
    using data::S1;
    using data::S2;
    using data::S3;
    using data::S4;
    using data::S5;

    std::cout << std::boolalpha;

    std::cout << "S1 has " << S1::_size << " elements\n";
    std::cout << "S2 has " << std::tuple_size_v<S2> << " elements\n";
    std::cout << "The first element of S1 is of type "
              << typeid(S1::_field<S1, 0>::type).name() << '\n';
    std::cout << "The first element of S2 is of type "
              << typeid(std::tuple_element_t<0, S2>).name() << '\n';

    S1 s1{1, false, "test"};
    S2 s2{};
    sr::copy_same_name_fields(s1, s2);
    dump_obj(s2);
    s2.v2 = true;
    // sr::copy_same_name_fields(s2, s1);  // won't compile
    sr::copy_same_name_fields<sr::missing_fields{1}>(s2, s1);
    dump_obj(s1);
    std::cout << s1 << '\n';  // "reflected" structs are like tuples (with care)
    S3 s3{s2, "test"};
    std::cout << s3 << '\n';  // output_range has nesting support
    dump_obj(s3);

    S4 s4{"Hello"};
    S5 s5{"world"};
    sr::copy(s4, s5);
    assert(!s4.value1.empty());
    assert(s5.value2 == "Hello");
    sr::copy(std::move(s4), s5);
    assert(s4.value1.empty());
    sr::get<0>(s4) = sr::get<0>(std::move(s5));
    assert(!s4.value1.empty());
    assert(s5.value2.empty());
    std::cout << s4 << '\n';
}
