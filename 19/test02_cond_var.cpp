#include <chrono>              // std::chrono::seconds
#include <condition_variable>  // std::condition_variable
#include <functional>          // std::ref
#include <iostream>            // std::cout
#include <mutex>               // std::mutex/unique_lock
#include <thread>              // std::thread/this_thread
#include <utility>             // std::move
#include "scoped_thread.h"     // scoped_thread

using namespace std;

void work(condition_variable& cv, mutex& cv_mut, bool& result_ready,
          int& result)
{
    this_thread::sleep_for(2s);
    result = 42;
    {
        unique_lock lock{cv_mut};
        result_ready = true;
    }
    cv.notify_one();
}

int main()
{
    condition_variable cv;
    mutex cv_mut;
    bool result_ready = false;
    int result;

    scoped_thread th{work, ref(cv), ref(cv_mut), ref(result_ready),
                     ref(result)};
    cout << "I am waiting now\n";
    unique_lock lock{cv_mut};
    cv.wait(lock, [&] { return result_ready; });
    cout << "Answer: " << result << '\n';
}
