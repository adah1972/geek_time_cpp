#include <memory>
#include "spdlog/async.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

using namespace std;
using namespace spdlog::sinks;

void set_multi_sink()
{
    auto console_sink = make_shared<stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::warn);
    console_sink->set_pattern("%H:%M:%S.%e %^%L%$ %v");

    auto file_sink =
        make_shared<rotating_file_sink_mt>("test.log", 1048576 * 5, 3);
    file_sink->set_level(spdlog::level::trace);
    file_sink->set_pattern("%Y-%m-%d %H:%M:%S.%f %L %v");

    spdlog::init_thread_pool(8192, 1);
    auto logger = shared_ptr<spdlog::async_logger>(new spdlog::async_logger(
        "multi_sink", {console_sink, file_sink}, spdlog::thread_pool(),
        spdlog::async_overflow_policy::block));
    logger->set_level(spdlog::level::debug);
    spdlog::set_default_logger(logger);
}

int main()
{
    set_multi_sink();
    spdlog::set_error_handler([](const std::string& msg) {
        spdlog::error("*** LOGGER ERROR ***: {}", msg);
    });
    spdlog::info("some invalid message to trigger an error {}{}{}{}", 3);
    spdlog::warn("this should appear in both console and file");
    spdlog::info(
        "this message should not appear in the console, only in the file");
}
