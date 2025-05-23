cmake_minimum_required(VERSION 3.12)
project(cxx20_misc)

# Check if the compiler supports C++20
include(CheckCXXCompilerFlag)
if(MSVC)
  check_cxx_compiler_flag("/std:c++20" COMPILER_SUPPORTS_CXX20)
else()
  check_cxx_compiler_flag("-std=c++20" COMPILER_SUPPORTS_CXX20)
endif()

if(NOT COMPILER_SUPPORTS_CXX20)
  message(WARNING "The compiler does not support C++20. Project is skipped.")
  return()
endif()

add_subdirectory(spaceship_op)
add_subdirectory(consteval)
add_subdirectory(constinit)
add_subdirectory(jthread)
