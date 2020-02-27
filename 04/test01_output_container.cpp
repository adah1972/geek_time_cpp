#include <iostream>            // std::cout/endl
#include <map>                 // std::map
#include <vector>              // std::vector
#include "output_container.h"  // operator<< for containers

using namespace std;

int main()
{
    map<int, int> mp{{1, 1}, {2, 4}, {3, 9}};
    cout << mp << endl;
    vector<vector<int>> vv{{1, 1}, {2, 4}, {3, 9}};
    cout << vv << endl;
}
