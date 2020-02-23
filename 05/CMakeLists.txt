cmake_minimum_required(VERSION 3.13)
project(container_examples)

set(CMAKE_CXX_STANDARD 17)

include_directories(../common)

add_executable(cntnr_test06_hash           test06_hash.cpp)
add_executable(cntnr_test07_priority_queue test07_priority_queue.cpp)
add_executable(cntnr_test08_unordered      test08_unordered.cpp)
add_executable(cntnr_test09_array          test09_array.cpp)
