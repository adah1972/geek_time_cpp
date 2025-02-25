cmake_minimum_required(VERSION 3.12)
project(range_update)

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

# CMake earlier than 3.20 does not support C++23
if(CMAKE_VERSION VERSION_LESS 3.20)
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  message(STATUS "C++20 will be used")
else()
  set(CMAKE_CXX_STANDARD 23)
  message(STATUS "C++23 will be tried")
endif()

find_package(Boost)

include_directories(../common)

add_executable(rgu_test01_sort            test01_sort.cpp)
add_executable(rgu_test02_fold            test02_fold.cpp)

if(Boost_FOUND)
  add_executable(rgu_test03_views_all     test03_views_all.cpp)
  target_include_directories(rgu_test03_views_all PRIVATE ${Boost_INCLUDE_DIRS})
endif()

add_executable(rgu_test04_iota            test04_iota.cpp)
add_executable(rgu_test05_take_drop       test05_take_drop.cpp)
add_executable(rgu_test06_split           test06_split.cpp)
add_executable(rgu_test07_join            test07_join.cpp)
add_executable(rgu_test08_views_bad_order test08_views_bad_order.cpp)
