#include <version>   // __cpp_lib_expected

#if __cpp_lib_expected >= 202211L

#include <climits>   // INT_MIN
#include <expected>  // std::expected/unexpected
#include <iostream>  // std::cout/endl
#include <string>    // std::string

using namespace std;

enum class div_errc {
    success,
    divide_by_zero,
    integer_divide_overflows,
    not_integer_division,
};

template <>
struct std::is_error_code_enum<div_errc> : true_type {
};

class div_errc_category : public error_category {
public:
    const char* name() const noexcept override
    {
        return "divide error";
    }
    string message(int c) const override
    {
        switch (static_cast<div_errc>(c)) {
        case div_errc::success:
            return "Successful";
        case div_errc::divide_by_zero:
            return "Divide by zero";
        case div_errc::integer_divide_overflows:
            return "Integer divide overflows";
        case div_errc::not_integer_division:
            return "Not integer division";
        }
        return "Unknown";
    }
    // Optional: Allow generic error conditions to be compared
    error_condition default_error_condition(int c) const noexcept override
    {
        switch (static_cast<div_errc>(c)) {
        case div_errc::success:
            break;
        case div_errc::divide_by_zero:
            return {errc::invalid_argument};
        case div_errc::integer_divide_overflows:
            return {errc::value_too_large};
        case div_errc::not_integer_division:
            return {errc::result_out_of_range};
        }
        return {c, *this};
    }
};

error_code make_error_code(div_errc e)
{
    static div_errc_category category;
    return {static_cast<int>(e), category};
}

expected<int, error_code> safe_divide(int i, int j)
{
    if (j == 0) {
        return unexpected(div_errc::divide_by_zero);
    }
    if (i == INT_MIN && j == -1) {
        return unexpected(div_errc::integer_divide_overflows);
    }
    if (i % j != 0) {
        return unexpected(div_errc::not_integer_division);
    }
    return i / j;
}

expected<int, error_code> caller(int i, int j, int k)
{
    return safe_divide(j, k).transform([i](int q) { return i + q; });
}

void print_error(ostream& os, const error_code& ec)
{
    os << ec.category().name() << ": " << ec.message();
}

template <typename T, typename E>
ostream& operator<<(ostream& os, const expected<T, E>& exp)
{
    if (exp) {
        os << exp.value();
    } else {
        print_error(os, exp.error());
    }
    return os;
}

#define CHECK(expr)                                            \
    {                                                          \
        auto result = (expr);                                  \
        cout << result;                                        \
        if (result == unexpected(div_errc::divide_by_zero)) {  \
            cout << ": Are you serious?";                      \
        } else if (result == 42) {                             \
            cout << ": Ha, I got you!";                        \
        }                                                      \
        cout << endl;                                          \
    }

int main()
{
    CHECK(caller(2, 1, 0));
    CHECK(caller(37, 20, 7));
    CHECK(caller(39, 21, 7));
}

#else

#include <iostream>  // std::cout

int main()
{
    std::cout << "std::expected is not supported in your environment\n";
}

#endif
