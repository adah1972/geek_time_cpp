#include "easylogging++.h"
INITIALIZE_EASYLOGGINGPP

void boom()
{
    char* ptr = nullptr;
    *ptr = '\0';
}

int main()
{
    el::Configurations conf{"log.conf"};
    el::Loggers::reconfigureAllLoggers(conf);
    boom();
}
