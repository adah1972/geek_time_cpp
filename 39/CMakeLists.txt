cmake_minimum_required(VERSION 3.10)
project(compile_time_string_examples)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU AND
    CMAKE_CXX_COMPILER_VERSION VERSION_LESS 10.0)
  set(CMAKE_CXX_STANDARD 17)
elseif(CMAKE_CXX_COMPILER_ID MATCHES Clang AND
    CMAKE_CXX_COMPILER_VERSION VERSION_LESS 12.0)
  set(CMAKE_CXX_STANDARD 17)
else()
  set(CMAKE_CXX_STANDARD 20)
endif()

add_executable(cts_test01_carg test01_carg.cpp )
add_executable(cts_test02_cts  test02_cts.cpp)
