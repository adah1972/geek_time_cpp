cmake_minimum_required(VERSION 3.10)
project(performance_test_examples)

set(CMAKE_CXX_STANDARD 17)

include_directories(../common)

add_compile_options(-O2)

add_executable(perf_test01_puzzle       test01_puzzle.cpp)
add_executable(perf_test02_volatile     test02_volatile.cpp)
add_executable(perf_test03_func_global  test03_func_global.cpp)
add_executable(perf_test04_profiler     test04_profiler.cpp ../common/profiler.cpp)
