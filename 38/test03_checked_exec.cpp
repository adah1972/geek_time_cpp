#include <ios>       // std::boolalpha
#include <iostream>  // std::cout/endl
#include <utility>   // std::forward

using namespace std;

namespace my {

// Linux may define an error_t, so the test is defined in my namespace

enum class error_t {
  ok,
  error,
  critical,
};

error_t check1()
{
    return error_t::ok;
}

error_t check2(int)
{
    return error_t::ok;
}

error_t check3(const char*)
{
    return error_t::error;
}

error_t check4()
{
    return error_t::critical;
}

template <typename R, typename... Fn>
R checked_exec(const R& expected, Fn&&... fn)
{
    R result = expected;
    (void)(((result = std::forward<Fn>(fn)()) == expected) && ...);
    return result;
}

void test_checked_exec(int n, const char* file)
{
    cout << boolalpha;
    cout << "check1 is OK: "
         << (checked_exec(error_t::ok, check1)
             == error_t::ok)
         << endl;
    cout << "check2 and check2 are OK: "
         << (checked_exec(
                 error_t::ok,
                 [&] { return check1(); },
                 [&] { return check2(n); })
             == error_t::ok)
         << endl;
    cout << "Checking all fails at check3: "
         << (checked_exec(
                 error_t::ok,
                 [&] { return check1(); },
                 [&] { return check2(n); },
                 [&] { return check3(file); },
                 [&] { return check4(); })
             == error_t::error)
         << endl;
}

}  // namespace my

int main(int argc, char* argv[])
{
    my::test_checked_exec(argc, argv[0]);
}
