#include <chrono>    // std::chrono::seconds
#include <future>    // std::promise
#include <iostream>  // std::cout
#include <thread>    // std::thread/this_thread
#include <utility>   // std::forward/move

using namespace std;

class scoped_thread {
public:
    template <typename... Arg>
    scoped_thread(Arg&&... arg)
        : thread_(std::forward<Arg>(arg)...)
    {
    }
    scoped_thread(scoped_thread&& other)
        : thread_(std::move(other.thread_))
    {
    }
    ~scoped_thread()
    {
        if (thread_.joinable()) {
            thread_.join();
        }
    }

private:
    thread thread_;
};

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
