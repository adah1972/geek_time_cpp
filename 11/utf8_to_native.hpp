#ifndef UTF8_TO_NATIVE_HPP
#define UTF8_TO_NATIVE_HPP

#include <string>

#if defined(_WIN32) || defined(_UNICODE)

std::wstring utf8_to_wstring(const char* str);
std::wstring utf8_to_wstring(const std::string& str);

#define NATIVE_STR(s) utf8_to_wstring(s).c_str()

#else

inline const char* to_c_str(const char* str)
{
    return str;
}

inline const char* to_c_str(const std::string& str)
{
    return str.c_str();
}

#define NATIVE_STR(s) to_c_str(s)

#endif

#endif // UTF8_TO_NATIVE_HPP
