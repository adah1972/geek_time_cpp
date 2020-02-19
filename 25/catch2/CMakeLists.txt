cmake_minimum_required(VERSION 3.13)
project(catch2_examples)

set(CMAKE_CXX_STANDARD 17)

include_directories(../../3rd-party/nvwa)

add_executable(c2_test01_simple c2_test01_simple.cpp)
add_executable(c2_test02_bdd    c2_test02_bdd.cpp c2_test_main.cpp)
add_executable(c2_test03_split  c2_test03_split.cpp c2_test_main.cpp)
