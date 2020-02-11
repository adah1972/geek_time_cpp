#include <chrono>
#include <thread>
#include "easylogging++.h"
INITIALIZE_EASYLOGGINGPP

void foo()
{
    TIMED_FUNC(timer);
    LOG(WARNING) << "A warning message";
}

void bar()
{
    using namespace std::literals;
    TIMED_SCOPE(timer1, "void bar()");
    foo();
    foo();
    TIMED_BLOCK(timer2, "a block")
    {
        foo();
        std::this_thread::sleep_for(100us);
    }
}

int main()
{
    el::Configurations conf{"log.conf"};
    el::Loggers::reconfigureAllLoggers(conf);
    bar();
}
