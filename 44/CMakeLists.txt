cmake_minimum_required(VERSION 3.12)
project(chrono_examples)

# Check if the compiler supports C++20
include(CheckCXXCompilerFlag)
if(MSVC)
  check_cxx_compiler_flag("/std:c++20" COMPILER_SUPPORTS_CXX20)
else()
  check_cxx_compiler_flag("-std=c++20" COMPILER_SUPPORTS_CXX20)
endif()

if(COMPILER_SUPPORTS_CXX20)
  set(CMAKE_CXX_STANDARD 20)
else()
  set(CMAKE_CXX_STANDARD 17)
endif()

add_executable(chr_test01_posix_time            test01_c89_posix_time.cpp)
add_executable(chr_test02_cxx11_chrono          test02_cxx11_chrono.cpp)
add_executable(chr_test03_cxx20_time_output     test03_cxx20_time_output.cpp)
add_executable(chr_test04_cxx20_date            test04_cxx20_date.cpp)
add_executable(chr_test05_cxx20_time_zone       test05_cxx20_time_zone.cpp)
add_executable(chr_test06_china_daylight_saving test06_china_daylight_saving.cpp)
