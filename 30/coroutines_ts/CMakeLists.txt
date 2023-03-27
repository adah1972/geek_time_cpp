cmake_minimum_required(VERSION 3.10)
project(coroutines_ts_example)

if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
  if(WIN32)
    add_compile_options(/std:c++latest
                        -fms-compatibility -Xclang -fcoroutines-ts)
  elseif(UNIX OR APPLE)
    add_compile_options(-std=c++17 -fcoroutines-ts)
  endif()

elseif(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  add_compile_options(-std=c++20 -fcoroutines)

elseif(MSVC)
  add_compile_options(/std:c++latest /await)

else()
  message(FATAL_ERROR "Unrecognized compiler")

endif()

add_executable(fibonacci_coroutines_ts fibonacci_coroutines_ts.cpp)
