#include <chrono>    // std::chrono::milliseconds
#include <complex>   // std::complex
#include <iostream>  // std::cout/endl
#include <string>    // std::string
#include <thread>    // std::this_thread

using namespace std;

int main()
{
    cout << "i * i = " << 1i * 1i << endl;
    cout << "Waiting for 500ms" << endl;
    this_thread::sleep_for(500ms);
    cout << "Hello world"s.substr(0, 5) << endl;
}
