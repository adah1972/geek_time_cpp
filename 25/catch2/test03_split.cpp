#include "nvwa/split.h"  // nvwa::split
#include <cstddef>       // size_t
#include <string>        // std::string
#include <string_view>   // std::string_view
#include <vector>        // std::vector
#include "catch.hpp"     // TEST_CASE/CHECK

using namespace std;
using nvwa::split;

TEST_CASE("Split_test", "[split]")
{
    using namespace std::literals;

    string_view str{"&grant_type=client_credential"
                    "&appid="
                    "&secret=APPSECRET"};

    vector<string> split_result_expected{"",
                                         "grant_type=client_"
                                         "credential",
                                         "appid=", "secret=APPSECRET"};

    auto result = split(str, '&');
    auto result_s = result.to_vector();
    auto result_sv = result.to_vector_sv();
    CHECK(result_s == split_result_expected);
    CHECK(result_s.size() == result_sv.size());
    {
        auto it = result_sv.begin();
        for (auto& s : result_s) {
            CHECK(s == *it);
            ++it;
        }
    }

    size_t i = 0;
    auto it = result.begin();
    auto end = result.end();
    for (; it != end && i < result_s.size(); ++it) {
        CHECK(*it == result_s[i]);
        ++i;
    }
    CHECK(it == end);
}
