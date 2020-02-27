#include "utf8_to_native.hpp"

#if defined(_WIN32) || defined(_UNICODE)
#include <windows.h>     // GetLastError/MultiByteToWideChar
#include <string>        // std::string
#include <system_error>  // std::error_code/system_category/system_error

namespace {

void throw_system_error(const char* reason)
{
    std::string msg(reason);
    msg += " failed";
    std::error_code ec(GetLastError(), std::system_category());
    throw std::system_error(ec, msg);
}

} /* unnamed namespace */

std::wstring utf8_to_wstring(const char* str)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, str, -1, nullptr, 0);
    if (len == 0) {
        throw_system_error("utf8_to_wstring");
    }
    std::wstring result(len - 1, L'\0');
    if (MultiByteToWideChar(CP_UTF8, 0, str, -1, result.data(), len) == 0) {
        throw_system_error("utf8_to_wstring");
    }
    return result;
}

std::wstring utf8_to_wstring(const std::string& str)
{
    return utf8_to_wstring(str.c_str());
}

#endif
