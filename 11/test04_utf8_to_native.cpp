#include <fstream>             // std::ifstream
#include <iostream>            // std::cout/endl
#include "utf8_to_native.hpp"  // NATIVE_STR

int main()
{
    using namespace std;
    const char filename[] = u8"测试.txt";
    ifstream ifs(NATIVE_STR(filename));
    cout << "File is " << (ifs ? "" : "not ") << "found." << endl;
}
