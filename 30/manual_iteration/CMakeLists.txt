cmake_minimum_required(VERSION 3.13)
project(manual_iteration)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  add_compile_options(-std=c++17 -fconcepts)
elseif(MSVC)
  add_compile_options(/std:c++latest /permissive-)
else()
  message(FATAL_ERROR "Unrecognized compiler")
endif()

include_directories(../../3rd-party/cmcstl2/include)

add_executable(test_fibonacci test_fibonacci.cpp)
