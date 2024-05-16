#include <chrono>           // std::chrono::seconds
#include <future>           // std::promise
#include <iostream>         // std::cout
#include <thread>           // std::thread/this_thread
#include <utility>          // std::move
#include "scoped_thread.h"  // scoped_thread

using namespace std;

void work(promise<int> prom)
{
    this_thread::sleep_for(2s);
    prom.set_value(42);
}

int main()
{
    promise<int> prom;
    auto fut = prom.get_future();
    scoped_thread th{work, std::move(prom)};
    cout << "I am waiting now\n";
    cout << "Answer: " << fut.get() << '\n';
}
