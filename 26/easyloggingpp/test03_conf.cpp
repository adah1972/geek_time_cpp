#include "easylogging++.h"
INITIALIZE_EASYLOGGINGPP

int main()
{
    el::Configurations conf{"log.conf"};
    el::Loggers::reconfigureAllLoggers(conf);
    LOG(DEBUG) << "A debug message";
    LOG(INFO) << "An info message";
}
