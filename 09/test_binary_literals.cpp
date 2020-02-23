#include <bitset>
#include <iostream>

using namespace std;

int main()
{
    unsigned mask = 0b111000000;
    cout << bitset<9>(mask) << endl;
}
