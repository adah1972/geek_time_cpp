cmake_minimum_required(VERSION 3.10)
project(container_examples)

set(CMAKE_CXX_STANDARD 17)

include_directories(../common)

add_executable(cntnr_test01_output_container test01_output_container.cpp)
add_executable(cntnr_test02_vector           test02_vector.cpp)
add_executable(cntnr_test03_list             test03_list.cpp)
add_executable(cntnr_test04_queue            test04_queue.cpp)
add_executable(cntnr_test05_stack            test05_stack.cpp)
