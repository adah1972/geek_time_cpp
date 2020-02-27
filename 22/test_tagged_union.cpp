#include <iostream>  // std::cout/endl
#include <string>    // std::string

using namespace std;

struct StringIntChar {
    enum { String, Int, Char } type;
    ~StringIntChar()
    {
        if (type == String) {
            string_value.~string();
        }
    }
    union {
        string string_value;
        int int_value;
        char char_value;
    };
};

int main()
{
    StringIntChar obj{.type = StringIntChar::String,
                      .string_value = "Hello world"s};
    cout << obj.string_value << endl;
}
