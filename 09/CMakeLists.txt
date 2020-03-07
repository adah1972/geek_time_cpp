cmake_minimum_required(VERSION 3.10)
project(literal_examples)

set(CMAKE_CXX_STANDARD 17)

add_executable(test_std_literals    test_std_literals.cpp)
add_executable(test_user_literals   test_user_literals.cpp)
add_executable(test_binary_literals test_binary_literals.cpp)
