#include <iostream>     // std::cout/endl
#include <string>       // std::string/getline
#include <string_view>  // std::string_view

using namespace std;

string greet(string_view name)
{
    string result("Hi, ");
    result += name;
    result += '!';
    return result;
}

int main()
{
    auto greeting = greet("C++");
    cout << greeting << endl;
    cout << "What's your name? ";
    string name;
    getline(cin, name);
    cout << greet(name) << endl;
}
