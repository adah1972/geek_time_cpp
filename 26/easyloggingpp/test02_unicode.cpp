#ifdef _WIN32
#include <fcntl.h>          // _O_WTEXT
#include <io.h>             // _setmode
#include <stdio.h>          // _fileno/stdout
#else
#include <iostream>         // std::wcout
#include <locale>           // std::locale
#endif
#include "easylogging++.h"  // easylogging++
INITIALIZE_EASYLOGGINGPP

int main()
{
#ifdef _WIN32
    _setmode(_fileno(stdout), _O_WTEXT);
#else
    using namespace std;
    locale::global(locale(""));
    wcout.imbue(locale());
#endif

    LOG(INFO) << L"测试 test";
    LOG(INFO) << "Narrow ASCII always OK";
}
