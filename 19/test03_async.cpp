#include <chrono>    // std::chrono::seconds
#include <future>    // std::async
#include <iostream>  // std::cout
#include <thread>    // std::this_thread

using namespace std;

int work()
{
    this_thread::sleep_for(2s);
    return 42;
}

int main()
{
    auto fut = async(launch::async, work);
    cout << "I am waiting now\n";
    cout << "Answer: " << fut.get() << '\n';
}
