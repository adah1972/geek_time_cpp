cmake_minimum_required(VERSION 3.10)
project(atomic_example)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads)

add_executable(test_singleton test_singleton.cpp singleton.cpp)
target_link_libraries(test_singleton ${CMAKE_THREAD_LIBS_INIT})
