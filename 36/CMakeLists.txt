cmake_minimum_required(VERSION 3.10)
project(view_test_examples)

set(CMAKE_CXX_STANDARD 20)

include_directories(../common ../third-party/gsl/include)

add_definitions(-DUSE_GSL)

if(MSVC)
  add_compile_options(/Zc:__cplusplus)
endif()

foreach(CompilerFlag
    CMAKE_CXX_FLAGS_RELEASE
    CMAKE_CXX_FLAGS_RELWITHDEBINFO
    CMAKE_CXX_FLAGS_MINSIZEREL
    CMAKE_C_FLAGS_RELEASE
    CMAKE_C_FLAGS_RELWITHDEBINFO
    CMAKE_C_FLAGS_MINSIZEREL)
  string(REGEX REPLACE "(^| )[/-]D *NDEBUG($| )" " "
         "${CompilerFlag}" "${${CompilerFlag}}")
endforeach()

add_executable(view_test01_string_view   test01_string_view.cpp)
add_executable(view_test02_span          test02_span.cpp)
add_executable(view_test03_span_perf     test03_span_perf.cpp
                                         ../common/profiler.cpp)
add_executable(view_test04_elements_view test04_elements_view.cpp)

if(NOT CMAKE_BUILD_TYPE)
  target_compile_options(view_test03_span_perf PRIVATE -O2)
endif()
