#include <chrono>    // std::chrono::*
#include <iomanip>   // std::setprecision
#include <iostream>  // std::cout

using namespace std::chrono;
using std::cout;
using std::setprecision;

int main()
{
    auto now = system_clock::now();
    cout << "to_time_t(now):     " << system_clock::to_time_t(now) << '\n';
    cout << "Seconds from epoch: " << setprecision(13)
         << duration_cast<duration<double>>(now.time_since_epoch()).count()
         << '\n';

    now -= 24h;
    cout << "24h ago:            " << now.time_since_epoch() / 1.0s << '\n';

    auto t1 = steady_clock::now();
    cout << "Hello world\n";
    auto t2 = steady_clock::now();
    cout << (t2 - t1) / 1ns << "ns has elapsed\n";

    seconds s{1};
    milliseconds ms = s;

    ms = milliseconds{1500};
    // s = ms;
    s = duration_cast<seconds>(ms);
    duration<double> fs = ms;
    // ms = fs;
    cout << fs.count() << "s\n";

    static_assert(1h * 10 == 10h);
    static_assert(1h / 1min == 60);
}
