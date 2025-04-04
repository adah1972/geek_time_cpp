#include <iostream>      // std::cout
#include <string>        // std::string
#include <string_view>
#if __has_include(<version>)
#include <version>       // __cpp_lib_constexpr_charconv/__cpp_lib_format
#endif

#if __cpp_lib_constexpr_charconv >= 202207L
#include <charconv>      // std::from_chars
#include <iterator>      // std::random_access_iterator
#include <system_error>  // std::errc
#endif

#define TEST_FORMAT_STD 1
#define TEST_FORMAT_FMT 2

#ifndef TEST_FORMAT
#if __cpp_lib_format >= 201907L
#define TEST_FORMAT TEST_FORMAT_STD
#elif __has_include(<fmt/format.h>)
#define TEST_FORMAT TEST_FORMAT_FMT
#endif
#endif

#if TEST_FORMAT == TEST_FORMAT_STD
#include <format>        // std::format
using std::format;
#define FMT_NS std
#elif TEST_FORMAT == TEST_FORMAT_FMT
#include <fmt/format.h>  // fmt::format
#define FMT_NS fmt
using fmt::format;
#endif

#if TEST_FORMAT

namespace my {

struct Point {
    double x;
    double y;
};

std::ostream& operator<<(std::ostream& os, const Point& pt)
{
    os << '(' << pt.x << ", " << pt.y << ')';
    return os;
}

} // namespace my

template <>
struct FMT_NS::formatter<my::Point> {
    constexpr auto parse(format_parse_context& ctx)
    {
        auto it = ctx.begin();
        auto end = ctx.end();

        parse_alignment(it, end);
        parse_sign(it, end);
        parse_hash(it, end);
        parse_width(it, end);
        parse_precision(it, end);
        parse_type(it, end);

        // Make sure we reached the end of the format specification
        if (it != end && *it != '}') {
            throw format_error("invalid format specifier");
        }

        return it;
    }

    auto format(const my::Point& p, format_context& ctx) const
    {
        // Format the elements
        auto fmt_str = build_format_string();
        auto x_str = format_element(fmt_str, p.x);
        auto y_str = format_element(fmt_str, p.y);

        // Combine into Point format and apply width/alignment
        if (width_ > 0) {
            auto result = FMT_NS::format("({}, {})", x_str, y_str);

            // Apply alignment and width
            if (alignment_ != '\0') {
                // Create a format string with alignment and fill
                std::string fmt = "{:";
                if (fill_ != ' ') {
                    fmt += fill_;
                }
                fmt += alignment_;
                fmt += std::to_string(width_);
                fmt += "}";

                return FMT_NS::vformat_to(ctx.out(), fmt,
                                          FMT_NS::make_format_args(result));
            } else {
                // Just width, no specific alignment
                return FMT_NS::format_to(ctx.out(), "{:{}}", result,
                                         width_);
            }
        }

        // Just combine into Point format without width/alignment
        return FMT_NS::format_to(ctx.out(), "({}, {})", x_str, y_str);
    }

private:
    template <typename Iterator>
    static constexpr void parse_number(Iterator& it, Iterator end,
                                       int& result)
    {
#if __cpp_lib_constexpr_charconv >= 202207L
        if (it != end && *it >= '0' && *it <= '9') {
            static_assert(std::random_access_iterator<Iterator>);
            // The expression &*it + (end - it) is convoluted but
            // necessary, as dereferencing the past-the-end iterator
            // is undefined behaviour.
            auto [ptr, ec] =
                std::from_chars(&*it, &*it + (end - it), result);
            if (ec != std::errc{}) {
                throw format_error("invalid number");
            }
            it += (ptr - &*it);
        }
#else
        if (it != end && *it >= '0' && *it <= '9') {
            unsigned value = 0;
            do {
                unsigned new_value = value * 10 + (*it - '0');
                if (new_value < value) {
                    throw format_error("invalid number");
                }
                value = new_value;
                ++it;
            } while (it != end && *it >= '0' && *it <= '9');
            result = static_cast<int>(value);
            if (result < 0) {
                throw format_error("invalid number");
            }
        }
#endif
    }

    constexpr void parse_alignment(format_parse_context::iterator& it,
                                   format_parse_context::iterator end)
    {
        if (it == end) {
            return;
        }

        // Check for fill character followed by alignment
        if (it + 1 != end) {
            char next = *(it + 1);
            if (next == '<' || next == '>' || next == '^') {
                fill_ = *it;
                alignment_ = next;
                it += 2;
                return;
            }
        }

        // Check for just alignment
        if (*it == '<' || *it == '>' || *it == '^') {
            alignment_ = *it++;
        }
    }

    constexpr void parse_sign(format_parse_context::iterator& it,
                              format_parse_context::iterator end)
    {
        if (it != end && (*it == '+' || *it == '-' || *it == ' ')) {
            sign_ = *it++;
        }
    }

    constexpr void parse_hash(format_parse_context::iterator& it,
                              format_parse_context::iterator end) {
        if (it != end && *it == '#') {
            hash_ = true;
            ++it;
        }
    }

    constexpr void parse_width(format_parse_context::iterator& it,
                               format_parse_context::iterator end)
    {
        // It is OK if width is absent (default to 0)
        parse_number(it, end, width_);
    }

    constexpr void parse_precision(format_parse_context::iterator& it,
                                   format_parse_context::iterator end)
    {
        if (it != end && *it == '.') {
            ++it;
            parse_number(it, end, precision_);
            // A number must follow '.' (default to -1, which is invalid here)
            if (precision_ < 0) {
                throw format_error("missing precision after '.'");
            }
        }
    }

    constexpr void parse_type(format_parse_context::iterator& it,
                              format_parse_context::iterator end)
    {
        if (it != end && *it != '}') {
            type_ = *it++;
            if (type_ != 'a' && type_ != 'A' &&
                type_ != 'e' && type_ != 'E' &&
                type_ != 'f' && type_ != 'F' &&
                type_ != 'g' && type_ != 'G') {
                throw format_error("invalid type specifier");
            }
        }
    }

    std::string build_format_string() const
    {
        std::string fmt_str = "{:";
        if (sign_ != '\0') {
            fmt_str += sign_;
        }
        if (hash_) {
            fmt_str += '#';
        }
        if (precision_ >= 0) {
            fmt_str += '.' + std::to_string(precision_);
        }
        if (type_ != '\0') {
            fmt_str += type_;
        }
        fmt_str += '}';
        return fmt_str;
    }

    static std::string format_element(std::string_view fmt_sv, double value)
    {
        return FMT_NS::vformat(fmt_sv, FMT_NS::make_format_args(value));
    }

    char fill_{' '};     // Fill character for padding
    char alignment_{};   // Alignment (left: '<'; right: '>'; center: '^')
    char sign_{};        // Sign for each element
    bool hash_{};        // Hash for each element
    int width_{};        // Width for the entire output
    int precision_{-1};  // Precision for each element
    char type_{};        // Format type for each element
};

using std::cout;

int main()
{
    my::Point pt{1.0, 2.0};
    cout << pt << '\n';
    cout << format("{}\n", pt);
    cout << format("{:+#}\n", pt);
    cout << format("{:*>15.1f}\n", pt);
}

#else

int main()
{
    std::cout << "format is not fully supported in your environment\n";
}

#endif
