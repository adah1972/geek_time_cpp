cmake_minimum_required(VERSION 3.12)
project(spaceship_op_example)

set(CMAKE_CXX_STANDARD 20)

include_directories(../../common)
add_executable(test_space_op main.cpp)
