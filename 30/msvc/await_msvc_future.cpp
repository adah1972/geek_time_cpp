#include <chrono>    // std::chrono::seconds
#include <future>    // std::async
#include <iostream>  // std::cout/endl
#include <thread>    // std::this_thread

using namespace std;

future<int> compute_value()
{
    int result = co_await async([] {
        this_thread::sleep_for(1s);
        return 42;
    });
    co_return result;
}

int main()
{
    auto value = compute_value();
    cout << value.get() << endl;
}
