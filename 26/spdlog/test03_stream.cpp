#include <vector>              // std::vector
#include "output_container.h"  // operator<< for containers
#include "spdlog/fmt/ostr.h"   // operator<< support in spdlog
#include "spdlog/spdlog.h"     // spdlog

using namespace std;

int main()
{
    vector<int> v{1, 2, 3};
    spdlog::info("Content of vector: {}", v);
}
