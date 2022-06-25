cmake_minimum_required(VERSION 3.10)
project(static_reflection_examples)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU AND
    CMAKE_CXX_COMPILER_VERSION VERSION_LESS 10.0)
  set(CMAKE_CXX_STANDARD 17)
elseif(CMAKE_CXX_COMPILER_ID MATCHES Clang AND
    CMAKE_CXX_COMPILER_VERSION VERSION_LESS 12.0)
  set(CMAKE_CXX_STANDARD 17)
else()
  set(CMAKE_CXX_STANDARD 20)
endif()

if(MSVC)
  add_compile_options(/Zc:__cplusplus /Zc:preprocessor)
endif()

include_directories(../common)

add_executable(test_static_reflection test_static_reflection.cpp )
