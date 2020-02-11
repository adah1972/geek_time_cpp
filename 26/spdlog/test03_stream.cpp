#include <memory>
#include <vector>
#include "output_container.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/spdlog.h"

using namespace std;

int main()
{
    vector<int> v{1, 2, 3};
    spdlog::info("Content of vector: {}", v);
}
