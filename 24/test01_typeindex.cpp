#include <iostream>              // std::cout/endl
#include <typeinfo>              // std::type_info
#include <utility>               // std::move
#include <vector>                // std::vector
#include <boost/type_index.hpp>  // boost::typeindex

using namespace std;
using boost::typeindex::type_id;
using boost::typeindex::type_id_with_cvr;

class shape {
public:
    virtual ~shape() = default;
};

class circle : public shape {};

int main()
{
    vector<int> v;
    auto it = v.cbegin();

    cout << "*** Using typeid\n";
    cout << typeid(const int).name() << endl;
    cout << typeid(decltype((v))).name() << endl;
    cout << typeid(it).name() << endl;

    cout << "*** Using type_id\n";
    cout << type_id<const int>() << endl;
    cout << type_id<decltype(v)>() << endl;
    cout << type_id<decltype(it)>() << endl;
    cout << type_id<decltype(__cplusplus)>() << endl;

    cout << "*** Using type_id_with_cvr\n";
    cout << type_id_with_cvr<const int>() << endl;
    cout << type_id_with_cvr<decltype((v))>() << endl;
    cout << type_id_with_cvr<decltype(move((v)))>() << endl;
    cout << type_id_with_cvr<decltype((it))>() << endl;

#define CHECK_TYPE_ID(object, type)                                        \
    cout << "type_id(" #object << ")"                                      \
         << (type_id<decltype(object)>() == type_id<type>() ? " is "       \
                                                            : " is NOT ")  \
         << #type "\n"
#define CHECK_TYPEID(object, type)                                         \
    cout << "typeid(" #object << ")"                                       \
         << (typeid(object) == typeid(type) ? " is " : " is NOT ")         \
         << #type "\n"

    cout << "*** Comparison w/ RTTI\n";
    shape* ptr = new circle();
    CHECK_TYPEID(*ptr, shape);
    CHECK_TYPEID(*ptr, circle);
    CHECK_TYPE_ID(*ptr, shape);
    CHECK_TYPE_ID(*ptr, circle);
    delete ptr;
}
