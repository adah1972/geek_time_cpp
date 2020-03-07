cmake_minimum_required(VERSION 3.10)
project(catch2_examples)

set(CMAKE_CXX_STANDARD 17)

include_directories(../../3rd-party/nvwa)

add_executable(c2_test01_simple test01_simple.cpp)
add_executable(c2_test02_bdd    test02_bdd.cpp test_main.cpp)
add_executable(c2_test03_split  test03_split.cpp test_main.cpp)
