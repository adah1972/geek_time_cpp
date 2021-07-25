#include <functional>           // std::bind/bind2nd/function/plus
#include <iostream>             // std::cout/endl
#include <map>                  // std::map
#include <string>               // std::string
#include <nvwa/c++_features.h>  // NVWA_USES_CXX17

using namespace std;

struct adder {
    adder(int n) : n_(n) {}
    int operator()(int x) const
    {
        return x + n_;
    }

private:
    int n_;
};

int main()
{
    using namespace std::placeholders;

    {
        adder add_2(2);
        cout << "Manual function object: " << add_2(5) << endl;
    }

#if !NVWA_USES_CXX17
    {
        cout << "bind2nd: " << bind2nd(plus<int>(), 2)(5) << endl;
    }
#endif

#if NVWA_CXX11_MODE
    {
        auto add_2 = bind(plus<int>(), _1, 2);
        cout << "bind: " << add_2(5) << endl;
    }

    {
        auto add_2 = [](int x) { return x + 2; };
        cout << "Lambda: " << add_2(5) << endl;
    }

    {
        auto adder = [](int n) { return [n](int x) { return x + n; }; };
        cout << "Currying: " << adder(2)(5) << endl;
    }

    {
        map<string, function<int(int, int)>> op_dict{
            {"+", [](int x, int y) { return x + y; }},
            {"-", [](int x, int y) { return x - y; }},
            {"*", [](int x, int y) { return x * y; }},
            {"/", [](int x, int y) { return x / y; }},
        };
        cout << "std::function: " << op_dict.at("+")(1, 6) << endl;
    }
#endif
}
