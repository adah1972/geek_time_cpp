cmake_minimum_required(VERSION 3.10)
project(armadillo_example)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
  find_package(Armadillo CONFIG REQUIRED)
else()
  find_package(Armadillo REQUIRED)
endif()

add_executable(arma_test arma_test.cpp)

target_link_libraries(arma_test PRIVATE ${ARMADILLO_LIBRARIES})
