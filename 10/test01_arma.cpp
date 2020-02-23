#include <armadillo>
#include <iostream>

using arma::imat22;
using std::cout;

int main()
{
    imat22 a{{1, 1}, {2, 2}};
    imat22 b{{1, 0}, {0, 1}};
    imat22 c{{2, 2}, {1, 1}};
    imat22 r = a * b + c;
    cout << r;
}
