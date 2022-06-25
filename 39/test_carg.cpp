#include <array>   // std::array
#include <cstdio>  // std::puts

using namespace std;

#define CARG typename
#define CARG_WRAP(x) [] { return (x); }
#define CARG_UNWRAP(x) (x)()

namespace strtools {

constexpr size_t length(const char* str)
{
    size_t count = 0;
    while (*str != '\0') {
        ++str;
        ++count;
    }
    return count;
}

constexpr const char* find(const char* str, char ch)
{
    while (*str != '\0') {
        if (*str == ch) {
            return str;
        }
        ++str;
    }
    return nullptr;
}

template <size_t Count>
constexpr auto copy_str(const char* str)
{
    array<char, Count + 1> result{};
    for (size_t i = 0; i < Count; ++i) {
        result[i] = str[i];
    }
    return result;
}

template <CARG Str>
constexpr auto remove_head(Str cpath)
{
    constexpr auto path = CARG_UNWRAP(cpath);
    constexpr auto skip = (path[0] == '/') ? 1 : 0;
    constexpr auto pos = &path[0] + skip;
    constexpr auto start = find(pos, '/');
    if constexpr (start == nullptr) {
        return copy_str<length(pos)>(pos);
    } else {
        return copy_str<length(start + 1)>(start + 1);
    }
}

}  // namespace strtools

int main()
{
    puts(strtools::remove_head(CARG_WRAP("/usr/local")).data());
}
