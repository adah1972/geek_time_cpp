cmake_minimum_required(VERSION 3.10)
project(functional_object_examples)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads)

include_directories(../third-party/nvwa)

add_executable(fo_test01_function_object test01_function_object.cpp)
add_executable(fo_test02_lambda_capture  test02_lambda_capture.cpp)
add_executable(fo_test03_generic_lambda  test03_generic_lambda.cpp)

target_link_libraries(fo_test02_lambda_capture PRIVATE
                      ${CMAKE_THREAD_LIBS_INIT})
