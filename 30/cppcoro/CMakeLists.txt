cmake_minimum_required(VERSION 3.13)
project(coroutines_ts_example)

if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
  if(WIN32)
    add_compile_options(/std:c++latest
                        -fms-compatibility -Xclang -fcoroutines-ts)
  elseif(UNIX OR APPLE)
    add_compile_options(-std=c++17 -stdlib=libc++ -fcoroutines-ts)
  endif()

elseif(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  add_compile_options(-std=c++17 -fcoroutines -fconcepts)
  set(HAVE_CONCEPTS 1)

elseif(MSVC)
  add_compile_options(/std:c++latest /await /permissive-)
  set(HAVE_CONCEPTS 1)

else()
  message(FATAL_ERROR "Unrecognized compiler")

endif()

include_directories(../../3rd-party/cppcoro/include)

add_executable(fibonacci_cppcoro_generator fibonacci_cppcoro_generator.cpp)

if(HAVE_CONCEPTS)
  include_directories(../../3rd-party/cmcstl2/include)
  add_executable(fibonacci_generator_view fibonacci_generator_view.cpp)
endif()
