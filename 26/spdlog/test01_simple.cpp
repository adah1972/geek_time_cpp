#include "spdlog/spdlog.h"

int main()
{
    spdlog::info("My first info log");
    spdlog::warn("Message with arg {}", 42);
    spdlog::error("{0:d}, {0:x}, {0:o}, {0:b}", 42);
}
