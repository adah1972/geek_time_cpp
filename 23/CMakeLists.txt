cmake_minimum_required(VERSION 3.10)
project(math_examples)

if(MSVC)
  find_package(Armadillo CONFIG)
else()
  find_package(Armadillo)
endif()

if(Armadillo_FOUND)
  add_subdirectory(armadillo)
endif()
add_subdirectory(boost_multiprecision)
