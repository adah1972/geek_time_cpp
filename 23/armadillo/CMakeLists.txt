cmake_minimum_required(VERSION 3.10)
project(armadillo_example)

set(CMAKE_CXX_STANDARD 17)

find_package(Armadillo CONFIG REQUIRED)

add_executable(arma_test arma_test.cpp)

target_link_libraries(arma_test PRIVATE ${ARMADILLO_LIBRARIES})
