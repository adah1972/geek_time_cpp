cmake_minimum_required(VERSION 3.13)
project(coroutine2_example)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.59 REQUIRED COMPONENTS context)

add_executable(fibonacci_coroutine2 fibonacci_coroutine2.cpp)
target_link_libraries(fibonacci_coroutine2 Boost::context)
