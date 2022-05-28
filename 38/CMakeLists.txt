cmake_minimum_required(VERSION 3.10)
project(fold_expression_test_examples)

set(CMAKE_CXX_STANDARD 17)

add_executable(fexpr_test01_sum          test01_sum.cpp)
add_executable(fexpr_test02_is_any_null  test02_is_any_null.cpp)
add_executable(fexpr_test03_checked_exec test03_checked_exec.cpp)
add_executable(fexpr_test04_print        test04_print.cpp)

