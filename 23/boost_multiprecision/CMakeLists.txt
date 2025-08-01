cmake_minimum_required(VERSION 3.10)
project(boost_multiprecision_examples)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake ${CMAKE_MODULE_PATH})

if(POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()
if(POLICY CMP0144)
  cmake_policy(SET CMP0144 NEW)
endif()

set(Boost_USE_MULTITHREADED OFF)
find_package(Boost REQUIRED)
find_package(GMP)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(bm_test01_cpp_int test01_cpp_int.cpp)
if(GMP_FOUND)
  add_executable(bm_test02_gmp_int test02_gmp_int.cpp)
  target_link_libraries(bm_test02_gmp_int PRIVATE ${GMP_LIBRARY})
endif(GMP_FOUND)
