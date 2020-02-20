#include <chrono>
#include <execution>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main()
{
    vector<double> v(10000000, 0.0625);

    {
        auto t1 = chrono::high_resolution_clock::now();
        double result = accumulate(v.begin(), v.end(), 0.0);
        auto t2 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> ms = t2 - t1;
        cout << "accumulate: result " << result << " took " << ms.count()
             << " ms\n";
    }

    {
        auto t1 = chrono::high_resolution_clock::now();
        double result = reduce(execution::par, v.begin(), v.end());
        auto t2 = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> ms = t2 - t1;
        cout << "reduce:     result " << result << " took " << ms.count()
             << " ms\n";
    }
}
