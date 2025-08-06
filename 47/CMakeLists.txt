cmake_minimum_required(VERSION 3.12)
project(object_lifetime)

set(CMAKE_CXX_STANDARD 20)

if(MSVC)
  add_compile_options(/Zc:__cplusplus)
endif()

find_package(fmt)

add_executable(olt_test01_bit_cast           test01_bit_cast.cpp)
add_executable(olt_test02_bad_cast           test02_bad_cast.cpp)
add_executable(olt_test03_mozi_serialization test03_mozi_serialization.cpp)

target_include_directories(olt_test03_mozi_serialization PRIVATE
                           ../third-party/mozi ../third-party/gsl/include)

if(fmt_FOUND AND fmt_VERSION VERSION_GREATER_EQUAL 9.0)
  target_compile_definitions(olt_test03_mozi_serialization PRIVATE
                             MOZI_PRINT_USE_FMTLIB)
  target_link_libraries(olt_test03_mozi_serialization fmt::fmt)
endif()
