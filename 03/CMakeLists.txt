cmake_minimum_required(VERSION 3.13)
project(value_category_examples)

set(CMAKE_CXX_STANDARD 17)

add_executable(vc_test01_lifetime           test01_lifetime.cpp)
add_executable(vc_test02_lifetime_extension test02_lifetime_extension.cpp)
add_executable(vc_test03_nrvo               test03_nrvo.cpp)
add_executable(vc_test04_forward            test04_forward.cpp)
