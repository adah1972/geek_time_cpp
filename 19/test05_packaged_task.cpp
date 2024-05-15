#include <chrono>    // std::chrono::seconds
#include <future>    // std::packaged_task
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
