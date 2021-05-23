#ifndef FIBONACCI_HPP
#define FIBONACCI_HPP

#include <iterator>  // std::input_iterator_tag
#include <stddef.h>  // ptrdiff_t
#include <stdint.h>  // uint64_t

class fibonacci {
public:
    class sentinel;
    class iterator;
    iterator begin() noexcept;
    sentinel end() noexcept;
};

class fibonacci::sentinel {};

class fibonacci::iterator {
public:
    // Required to satisfy iterator concept
    typedef ptrdiff_t difference_type;
    typedef uint64_t value_type;
    typedef const uint64_t* pointer;
    typedef const uint64_t& reference;
    typedef std::input_iterator_tag iterator_category;

    value_type operator*() const { return b_; }
    pointer operator->() const { return &b_; }
    iterator& operator++()
    {
        auto tmp = a_;
        a_ = b_;
        b_ += tmp;
        return *this;
    }
    iterator operator++(int)
    {
        auto tmp = *this;
        ++*this;
        return tmp;
    }
    bool operator==(const sentinel&) const { return false; }
    bool operator!=(const sentinel&) const { return true; }

private:
    uint64_t a_{0};
    uint64_t b_{1};
};

// sentinel needs to be equality_comparable_with iterator
bool operator==(const fibonacci::sentinel& lhs,
                const fibonacci::iterator& rhs)
{
    return rhs == lhs;
}
bool operator!=(const fibonacci::sentinel& lhs,
                const fibonacci::iterator& rhs)
{
    return rhs != lhs;
}

inline fibonacci::iterator fibonacci::begin() noexcept
{
  return iterator();
}

inline fibonacci::sentinel fibonacci::end() noexcept
{
    return sentinel();
}

#if __cplusplus > 201703L && __has_include(<ranges>)
#include <ranges>

namespace std::ranges {

template <>
inline constexpr bool enable_borrowed_range<fibonacci> = true;

}
#endif

#endif // FIBONACCI_HPP
