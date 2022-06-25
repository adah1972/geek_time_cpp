cmake_minimum_required(VERSION 3.10)
project(memory_context_examples)

set(CMAKE_CXX_STANDARD 17)

add_executable(mc_test01_normal         test01_normal.cpp
               memory_context.cpp)
add_executable(mc_test02_leak           test02_leak.cpp
               memory_context.cpp)
add_executable(mc_test03_double_free    test03_double_free.cpp
               memory_context.cpp)
add_executable(mc_test04_memory_corrupt test04_memory_corrupt.cpp
               memory_context.cpp)
