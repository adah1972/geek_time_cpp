#include <iostream>
#include <string>
#include <unicode/unistr.h>
#include <unicode/ustream.h>

using namespace std;
using icu::UnicodeString;

int main()
{
    auto str = UnicodeString::fromUTF8(u8"你好");
    cout << str << endl;
    string u8str;
    str.toUTF8String(u8str);
    cout << "In UTF-8 it is " << u8str.size() << " bytes" << endl;
}
