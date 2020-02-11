#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#else
#include <locale>
#endif
#include "easylogging++.h"
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
