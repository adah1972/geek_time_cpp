cmake_minimum_required(VERSION 3.13)
project(lifetime_examples)

set(CMAKE_CXX_STANDARD 17)

include_directories(../common)

add_executable(lt_test01_stack_unwind  test01_stack_unwind.cpp)
add_executable(lt_test02_shape_wrapper test02_shape_wrapper.cpp)
