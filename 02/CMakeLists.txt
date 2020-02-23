cmake_minimum_required(VERSION 3.13)
project(smart_ptr_examples)

set(CMAKE_CXX_STANDARD 17)

include_directories(../common)

add_executable(sp_test01_unique_ptr test01_unique_ptr.cpp)
add_executable(sp_test02_shared_ptr test02_shared_ptr.cpp)
