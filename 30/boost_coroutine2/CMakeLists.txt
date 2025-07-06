cmake_minimum_required(VERSION 3.10)
project(coroutine2_example)

set(CMAKE_CXX_STANDARD 17)

if(POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()
if(POLICY CMP0144)
  cmake_policy(SET CMP0144 NEW)
endif()

find_package(Boost REQUIRED context)

add_executable(fibonacci_coroutine2 fibonacci_coroutine2.cpp)
target_link_libraries(fibonacci_coroutine2 Boost::context)
