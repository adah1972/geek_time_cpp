#include <chrono>    // std::chrono::milliseconds
#include <iostream>  // std::cout
#include <mutex>     // std::mutex/lock_guard
#include <thread>    // std::thread/this_thread

using namespace std;

mutex output_lock;

void func(const char* name)
{
    this_thread::sleep_for(100ms);
    lock_guard<mutex> guard{output_lock};
    cout << "I am thread " << name << '\n';
}

int main()
{
    thread t1{func, "A"};
    thread t2{func, "B"};
    t1.join();
    t2.join();
}
