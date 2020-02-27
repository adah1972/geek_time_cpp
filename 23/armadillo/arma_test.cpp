#include <armadillo>  // arma::datum/mat/vec
#include <cmath>      // std::cos/sin
#include <iomanip>    // std::setprecision/setw
#include <iostream>   // std::cout/fixed

using namespace std;

int main()
{
    arma::vec pos{1.0, 0.0};

    auto& pi = arma::datum::pi;
    double angle = pi / 2;
    arma::mat rot = {
        {cos(angle), -sin(angle)},
        {sin(angle), cos(angle)}};

    cout << "Current position:\n" << pos;
    cout << "Rotating " << angle * 180 / pi << " deg\n";

    arma::vec new_pos = rot * pos;
    cout << "New position:\n" << new_pos;

    cout << fixed << setw(9) << setprecision(4);
    new_pos.raw_print(cout, "New position:");

    cout << fixed << setw(9) << setprecision(4);
    new_pos.t().raw_print(cout, "New position:");
}
