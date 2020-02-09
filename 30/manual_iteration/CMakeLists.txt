cmake_minimum_required(VERSION 3.13)
project(manual_iteration)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
      -std=c++17 -fconcepts")
elseif(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
      /std:c++latest /permissive-")
else()
  message(FATAL_ERROR "Unrecognized compiler")
endif()

include_directories(${PROJECT_SOURCE_DIR}/../../3rd-party/cmcstl2/include)

add_executable(test_fibonacci test_fibonacci.cpp)
