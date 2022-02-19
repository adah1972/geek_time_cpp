cmake_minimum_required(VERSION 3.10)
project(manual_iteration)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 10.0)
    add_compile_options(-std=c++20)
  else()
    add_compile_options(-std=c++17 -fconcepts)
  endif()
elseif(MSVC)
  add_compile_options(/std:c++latest /permissive-)
else()
  message(FATAL_ERROR "Unrecognized compiler")
endif()

include_directories(../../third-party/cmcstl2/include)

add_executable(test_fibonacci test_fibonacci.cpp)
