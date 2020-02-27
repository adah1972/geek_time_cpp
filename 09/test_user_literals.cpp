#include <iostream>  // std::cout/endl

using namespace std;

struct length {
    double value;
    enum unit {
        metre,
        kilometre,
        millimetre,
        centimetre,
        inch,
        foot,
        yard,
        mile,
    };
    static constexpr double factors[] = {1.0,    1000.0, 1e-3,   1e-2,
                                         0.0254, 0.3048, 0.9144, 1609.344};
    explicit length(double v, unit u = metre) { value = v * factors[u]; }
};

length operator+(length lhs, length rhs)
{
    return length(lhs.value + rhs.value);
}

length operator"" _m(long double v)
{
    return length(v, length::metre);
}

length operator"" _cm(long double v)
{
    return length(v, length::centimetre);
}

int main()
{
    auto result = 1.0_m + 10.0_cm;
    cout << "Result is " << result.value << "m\n";
}
