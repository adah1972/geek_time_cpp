cmake_minimum_required(VERSION 3.13)
project(lecture_22_examples)

if(MSVC)
  add_compile_options(/std:c++latest)
else()
  set(CMAKE_CXX_STANDARD 17)
endif()

include_directories(${PROJECT_SOURCE_DIR}/../3rd-party/expected/include)
include_directories(${PROJECT_SOURCE_DIR}/../3rd-party/nvwa)

add_executable(test_optional     test_optional.cpp)
if(NOT CMAKE_CXX_COMPILER_ID MATCHES GNU OR
   CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 8)
# GCC 7 (or lower) does not support non-trivial designated initializers
add_executable(test_tagged_union test_tagged_union.cpp)
endif()
add_executable(test_variant      test_variant.cpp)
add_executable(test_expected     test_expected.cpp)
