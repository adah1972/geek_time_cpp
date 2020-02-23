cmake_minimum_required(VERSION 3.13)
project(unicode_examples)

set(CMAKE_CXX_STANDARD 17)

find_package(ICU COMPONENTS "uc" "io")

add_executable(uc_test01_utf test01_utf.cpp)
add_executable(uc_test02_dump_str test02_dump_str.cpp)
add_executable(uc_test03_wcout test03_wcout.cpp)
add_executable(uc_test04_utf8_to_native test04_utf8_to_native.cpp
               utf8_to_native.cpp)

if(ICU_FOUND)
add_executable(uc_test05_icu test05_icu.cpp)
target_link_libraries(uc_test05_icu PRIVATE ICU::uc ICU::io)
endif()
