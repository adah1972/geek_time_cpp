#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#else
#include <locale>
#endif
#include <iostream>

int main()
{
#ifdef _WIN32
    _setmode(_fileno(stdout), _O_WTEXT);
#else
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale());
#endif
    std::wcout << L"中文 Español Français\n";
    std::wcout << "Narrow characters are "
                  "also OK on wcout\n";
    // but not on cout...
}
