cmake_minimum_required(VERSION 3.10)
project(coroutines_ts_example)

if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
  if(WIN32)
    add_compile_options(/std:c++latest
                        -fms-compatibility -Xclang -fcoroutines-ts)
  elseif(UNIX OR APPLE)
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 14.0)
      add_compile_options(-std=c++20)
    else()
      add_compile_options(-std=c++17 -fcoroutines-ts)
    endif()
  endif()

elseif(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  add_compile_options(-std=c++20 -fcoroutines)

elseif(MSVC)
  if(MSVC_VERSION GREATER_EQUAL 1930)
    add_compile_options(/std:c++20 /Zc:__cplusplus)
  else()
    add_compile_options(/std:c++latest /await)
  endif()

else()
  message(FATAL_ERROR "Unrecognized compiler")

endif()

add_executable(fibonacci_coroutines_ts fibonacci_coroutines_ts.cpp)
