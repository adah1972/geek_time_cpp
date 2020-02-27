#include <iostream>                // std::cout/endl
#include <stdexcept>               // std::invalid_argument
#include <string>                  // std::string/stoi
#include <boost/lexical_cast.hpp>  // boost::lexical_cast/bad_lexical_cast

using namespace std;
using boost::bad_lexical_cast;
using boost::lexical_cast;

int main()
{
    int d = 42;
    auto d_str = lexical_cast<string>(d);
    cout << d_str << endl;

    auto f = lexical_cast<float>(d_str) / 4.0;
    cout << f << endl;

    try {
        int t = lexical_cast<int>("x");
        cout << t << endl;
    }
    catch (bad_lexical_cast& e) {
        cout << e.what() << endl;
    }

    try {
        int t = std::stoi("x");
        cout << t << endl;
    }
    catch (invalid_argument& e) {
        cout << e.what() << endl;
    }
}
