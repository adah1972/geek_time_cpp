#include <iostream>     // std::cout
#include <thread>       // std::thread
#include <vector>       // std::vector
#include "singleton.h"  // singleton

using namespace std;

void do_something()
{
    singleton::instance()->do_something();
}

int main()
{
    constexpr int THREADS = 8;
    cout << "singleton will be created lazily only once\n";
    vector<thread> threads;
    for (int i = 0; i < THREADS; ++i) {
        threads.emplace_back(do_something);
    }
    for (auto& thrd : threads) {
        thrd.join();
    }
    singleton::destroy();
}
