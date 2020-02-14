cmake_minimum_required(VERSION 3.13)
project(math_examples)

find_package(Armadillo CONFIG)
if(Armadillo_FOUND)
  add_subdirectory(armadillo)
endif()
add_subdirectory(boost_multiprecision)
