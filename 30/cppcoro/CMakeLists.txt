cmake_minimum_required(VERSION 3.10)
project(coroutines_ts_example)

if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
  if(WIN32)
    add_compile_options(/std:c++latest
                        -fms-compatibility -Xclang -fcoroutines-ts)
  elseif(UNIX OR APPLE)
    if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 14.0)
      add_compile_options(-std=c++20)
      set(HAVE_CONCEPTS ON)
    else()
      add_compile_options(-std=c++17 -fcoroutines-ts)
    endif()
  endif()

elseif(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  add_compile_options(-std=c++20 -fcoroutines)
  set(HAVE_CONCEPTS ON)

elseif(MSVC)
  add_compile_options(/std:c++latest /await /permissive-)
  set(HAVE_CONCEPTS ON)

else()
  message(FATAL_ERROR "Unrecognized compiler")

endif()

include_directories(../../third-party/cppcoro/include)

add_executable(fibonacci_cppcoro_generator fibonacci_cppcoro_generator.cpp)

if(HAVE_CONCEPTS)
  include_directories(../../third-party/cmcstl2/include)
  add_executable(fibonacci_generator_view fibonacci_generator_view.cpp)
endif()
