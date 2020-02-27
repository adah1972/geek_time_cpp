#include <iomanip>    // std::setw
#include <iostream>   // std::cout/endl/hex
#include <stdexcept>  // std::runtime_error
#include <string>     // std::string/u16string

using namespace std;

const char32_t unicode_max = 0x10FFFF;

void to_utf_16(char32_t ch, u16string& result)
{
    if (ch > unicode_max) {
        throw runtime_error("invalid code point");
    }
    if (ch < 0x10000) {
        result += char16_t(ch);
    } else {
        char16_t first = 0xD800 | ((ch - 0x10000) >> 10);
        char16_t second = 0xDC00 | (ch & 0x3FF);
        result += first;
        result += second;
    }
}

void to_utf_8(char32_t ch, string& result)
{
    if (ch > unicode_max) {
        throw runtime_error("invalid code point");
    }
    if (ch < 0x80) {
        result += ch;
    } else if (ch < 0x800) {
        result += 0xC0 | (ch >> 6);
        result += 0x80 | (ch & 0x3F);
    } else if (ch < 0x10000) {
        result += 0xE0 | (ch >> 12);
        result += 0x80 | ((ch >> 6) & 0x3F);
        result += 0x80 | (ch & 0x3F);
    } else {
        result += 0xF0 | (ch >> 18);
        result += 0x80 | ((ch >> 12) & 0x3F);
        result += 0x80 | ((ch >> 6) & 0x3F);
        result += 0x80 | (ch & 0x3F);
    }
}

int main()
{
    char32_t str[] = U" \u6C49\U0001F600";
    u16string u16str;
    string u8str;
    for (auto ch : str) {
        if (ch == 0) {
            break;
        }
        to_utf_16(ch, u16str);
        to_utf_8(ch, u8str);
    }
    cout << hex << setfill('0');
    for (char16_t ch : u16str) {
        cout << setw(4) << unsigned(ch) << ' ';
    }
    cout << endl;
    for (unsigned char ch : u8str) {
        cout << setw(2) << unsigned(ch) << ' ';
    }
    cout << endl;
}
