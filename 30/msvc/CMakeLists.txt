cmake_minimum_required(VERSION 3.13)
project(msvc_specific_examples)

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
      /std:c++latest /await")
else()
  message(FATAL_ERROR "Unsupported compiler")
endif()

add_executable(fibonacci_msvc_generator fibonacci_msvc_generator.cpp)
add_executable(await_msvc_future await_msvc_future.cpp)
