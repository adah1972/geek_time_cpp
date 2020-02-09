cmake_minimum_required(VERSION 3.13)
project(range_examples)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
      -std=c++17 -fconcepts")
elseif(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
      /std:c++latest /permissive-")
else()
  message(FATAL_ERROR "Unrecognized compiler")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
    -I${PROJECT_SOURCE_DIR}/../3rd-party/cmcstl2/include\
    -I${PROJECT_SOURCE_DIR}/../3rd-party/nvwa")

add_executable(test01_sort               test01_sort.cpp)
add_executable(test02_reverse_view       test02_reverse_view.cpp)
add_executable(test03_filter_view        test03_filter_view.cpp)
add_executable(test04_filter_reverse     test04_filter_reverse.cpp)
add_executable(test05_null_sentinel      test05_null_sentinel.cpp)
add_executable(test06_squared_sum        test06_squared_sum.cpp)
#add_executable(test07_ranges_begin       test07_ranges_begin.cpp)
#add_executable(test08_ranges_v3_zip_sort test08_ranges_v3_zip_sort.cpp)
