cmake_minimum_required(VERSION 3.12)
project(jthread_example)

set(CMAKE_CXX_STANDARD 20)

include(../../libcxxdetect.cmake)

if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
  detect_libcxx()
  if(LIBCXX_FOUND)
    if(LIBCXX_VERSION VERSION_LESS 18)
      message(WARNING "The compiler does not support jthread. Project is skipped.")
      return()
    endif()
    if(LIBCXX_VERSION VERSION_GREATER_EQUAL 18 AND
       LIBCXX_VERSION VERSION_LESS 20)
      add_compile_options(-fexperimental-library)
    endif()
  endif()
endif()

add_executable(test_jthread test_jthread.cpp)

if(NOT WIN32)
  find_package(Threads)
  target_link_libraries(test_jthread PRIVATE Threads::Threads)
endif()
