#include <array>
#include <stdint.h>
#include <mozi/bit_fields.hpp>
#include <mozi/net_pack.hpp>
#include <mozi/print.hpp>
#include <mozi/serialization.hpp>
#include <mozi/struct_reflection.hpp>

using mozi::bit_field;
using mozi::bit_field_signed;

DEFINE_BIT_FIELDS_CONTAINER(                //
    Date,                                   //
    (bit_field<23, bit_field_signed>)year,  //
    (bit_field<4>)month,                    //
    (bit_field<5>)day                       //
);

DEFINE_STRUCT(                  //
    Data,                       //
    (std::array<char, 8>)name,  //
    (uint16_t)age,              //
    (Date)last_update           //
);

int main()
{
    Data data{{"John"}, 17, {2024, 8, 19}};
    mozi::println(data);

    mozi::serialize_t result;
    mozi::net_pack::serialize(data, result);
    mozi::println(result);
}
