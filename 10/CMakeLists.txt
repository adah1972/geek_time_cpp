cmake_minimum_required(VERSION 3.10)
project(return_value_examples)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
  find_package(Armadillo CONFIG)
else()
  find_package(Armadillo)
endif()

if(Armadillo_FOUND)
add_executable(rv_test01_arma        test01_arma.cpp)
include_directories(${ARMADILLO_INCLUDE_DIRS})
target_link_libraries(rv_test01_arma PRIVATE ${ARMADILLO_LIBRARIES})
endif()

add_executable(rv_test02_rvo_unnamed test02_rvo_unnamed.cpp)
add_executable(rv_test03_rvo_named   test03_rvo_named.cpp)
add_executable(rv_test04_rv_move     test04_rv_move.cpp)
add_executable(rv_test05_rv_copy     test05_rv_copy.cpp)
