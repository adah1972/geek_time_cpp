#include <iostream>  // std::cout/endl
#include <string>    // std::string

using namespace std;

struct StringIntChar {
    enum { String, Int, Char } type;
    StringIntChar(string value)
        : type(String)
        , string_value(std::move(value))
    {
    }
    StringIntChar(int value)
        : type(Int)
        , int_value(value)
    {
    }
    StringIntChar(char value)
        : type(Char)
        , char_value(value)
    {
    }
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
    StringIntChar obj{"Hello world"s};
    cout << obj.string_value << endl;
}
