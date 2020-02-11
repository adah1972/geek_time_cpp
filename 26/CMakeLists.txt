cmake_minimum_required(VERSION 3.13)
project(log_examples)

find_package(spdlog)

add_subdirectory(easyloggingpp)

if(spdlog_FOUND)
add_subdirectory(spdlog)
endif()
