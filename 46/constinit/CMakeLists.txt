cmake_minimum_required(VERSION 3.12)
project(const_init_example)

set(CMAKE_CXX_STANDARD 20)

if((CMAKE_CXX_COMPILER_ID STREQUAL GNU AND
    CMAKE_CXX_COMPILER_VERSION VERSION_LESS 12) OR
   (CMAKE_CXX_COMPILER_ID STREQUAL Clang AND
    CMAKE_CXX_COMPILER_VERSION VERSION_LESS 15) OR
   (CMAKE_CXX_COMPILER_ID STREQUAL AppleClang AND
    CMAKE_CXX_COMPILER_VERSION VERSION_LESS 14) OR
   (MSVC AND MSVC_VERSION LESS 1930))
  message(WARNING "The compiler cannot compile this example. Project is skipped.")
  return()
endif()

add_executable(test_const_init main.cpp primes.cpp)
