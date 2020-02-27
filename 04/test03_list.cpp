#include <algorithm>           // std::sort
#include <iostream>            // std::cout/endl
#include <list>                // std::list
#include <vector>              // std::vector
#include "output_container.h"  // operator<< for containers

using namespace std;

int main()
{
    list<int> lst{1, 7, 2, 8, 3};
    vector<int> vec{1, 7, 2, 8, 3};

    sort(vec.begin(), vec.end());
    // sort(lst.begin(), lst.end());
    lst.sort();

    cout << lst << endl;

    cout << vec << endl;
}
