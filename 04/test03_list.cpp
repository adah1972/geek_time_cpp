#include "output_container.h"
#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
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
