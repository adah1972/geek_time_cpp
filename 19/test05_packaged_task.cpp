#include <chrono>           // std::chrono::seconds
#include <future>           // std::packaged_task
#include <iostream>         // std::cout
#include <thread>           // std::thread/this_thread
#include <utility>          // std::move
#include "scoped_thread.h"  // scoped_thread

using namespace std;

int work()
{
    this_thread::sleep_for(2s);
    return 42;
}

int main()
{
    packaged_task<int()> task{work};
    auto fut = task.get_future();
    scoped_thread th{std::move(task)};
    this_thread::sleep_for(1s);
    cout << "I am waiting now\n";
    cout << "Answer: " << fut.get() << '\n';
}
