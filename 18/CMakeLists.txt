cmake_minimum_required(VERSION 3.10)
project(variadic_template_examples)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
  add_compile_options(/utf-8)
endif()

include_directories(../third-party/nvwa)

add_executable(vt_test01_sum        test01_sum.cpp)
add_executable(vt_test02_compose    test02_compose.cpp)
add_executable(vt_test03_tuple      test03_tuple.cpp)
add_executable(vt_test04_apply      test04_apply.cpp)
add_executable(vt_test05_count_bits test05_count_bits.cpp)
