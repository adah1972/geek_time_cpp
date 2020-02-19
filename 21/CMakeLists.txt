cmake_minimum_required(VERSION 3.13)
project(debug_new_examples)

set(CMAKE_CXX_STANDARD 17)

include_directories(../3rd-party/nvwa)

add_executable(test_debug_new_include test_debug_new_include.cpp
               ../3rd-party/nvwa/nvwa/debug_new.cpp)

if(CMAKE_BUILD_TYPE STREQUAL Debug AND
   CMAKE_CXX_COMPILER_ID MATCHES GNU OR CMAKE_CXX_COMPILER_ID MATCHES Clang)
  add_executable(test_debug_new_no_include test_debug_new_no_include.cpp
                 ../3rd-party/nvwa/nvwa/debug_new.cpp)
  set_target_properties(test_debug_new_no_include PROPERTIES COMPILE_FLAGS
                        -D_DEBUG_NEW_PROGNAME=\\"test_debug_new_no_include\\")
  if(APPLE)
    target_link_options(test_debug_new_no_include PRIVATE LINKER:-no_pie)
  endif(APPLE)
endif()
