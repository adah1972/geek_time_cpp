#include <chrono>    // std::chrono::milliseconds
#include <iostream>  // std::cout
#include <thread>    // std::jthread/stop_token/this_thread

using namespace std;

int main()
{
    {
        jthread th{[] {
            for (int i = 0; i < 5; ++i) {
                cout << i << '\n';
                this_thread::sleep_for(100ms);
            }
        }};
    }
    cout << "***\n";
    {
        jthread th{[](stop_token stoken) {
            for (int i = 0; i < 5; ++i) {
                if (stoken.stop_requested()) {
                    break;
                }
                cout << i << '\n';
                this_thread::sleep_for(100ms);
            }
        }};
        this_thread::sleep_for(180ms);
    }
    cout << "***\n";
    {
        jthread th{[](stop_token stoken) {
            for (int i = 0; i < 5; ++i) {
                if (stoken.stop_requested()) {
                    break;
                }
                cout << i << '\n';
                this_thread::sleep_for(100ms);
            }
        }};
        this_thread::sleep_for(80ms);
        th.request_stop();
        this_thread::sleep_for(100ms);
    }
}
