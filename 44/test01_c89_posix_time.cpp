#include <iostream>  // std::cout
#include <time.h>    // time_t/time/ctime/asctime/gmtime/...

using std::cout;

int main()
{
    time_t t = time(nullptr);
    cout << "Seconds since epoch time: " << t << '\n';
    cout << "ctime result:             " << ctime(&t);
    tm* tm_ptr = localtime(&t);
    cout << "Local time as ctime:      "
         << asctime(tm_ptr);
    tm_ptr = gmtime(&t);
    cout << "UTC time as ctime:        "
         << asctime(tm_ptr);
    char buffer[80];
    strftime(buffer, sizeof buffer, "%F %T %Z", tm_ptr);
    cout << "Formatted time:           " << buffer
#ifdef _WIN32
         << " (incorrect)"
#endif
         << '\n';
    cout << "Wrong mktime result:      " << mktime(tm_ptr) << '\n';
}
