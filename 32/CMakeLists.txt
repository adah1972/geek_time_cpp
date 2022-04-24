cmake_minimum_required(VERSION 3.10)
project(allocator_examples)

set(CMAKE_CXX_STANDARD 17)

include_directories(../common)

add_executable(alc_test01_allocator              test01_allocator.cpp)

if(MSVC OR CMAKE_CXX_COMPILER_ID MATCHES GNU)
  add_executable(alc_test02_pmr_new_delete_alloc test02_pmr_new_delete_alloc.cpp)
  add_executable(alc_test03_pmr_move             test03_pmr_move.cpp)
endif()
