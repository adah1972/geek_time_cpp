#include <chrono>
#include <future>
#include <iostream>
#include <thread>

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
