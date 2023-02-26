#include <vector>              // std::vector

#if defined(USE_FMT_RANGES) && __has_include(<fmt/ranges.h>)

#include <fmt/ranges.h>
#include <spdlog/spdlog.h>

#else

#include "output_container.h"  // operator<< for containers

#include <spdlog/spdlog.h>     // spdlog
#include <spdlog/fmt/ostr.h>   // operator<< support in spdlog

#if FMT_VERSION >= 90000
template <> struct fmt::formatter<std::vector<int>> : ostream_formatter {};
#endif

#endif

using namespace std;

int main()
{
    vector<int> v{1, 2, 3};
    spdlog::info("Content of vector: {}", v);
}
