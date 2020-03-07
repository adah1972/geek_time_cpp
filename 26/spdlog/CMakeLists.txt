cmake_minimum_required(VERSION 3.10)
project(spdlog_examples)

set(CMAKE_CXX_STANDARD 17)

find_package(spdlog CONFIG REQUIRED)

include_directories(../../common)

set(USED_LIBS spdlog::spdlog)

add_executable(sl_test01_simple     test01_simple.cpp)
add_executable(sl_test02_multi_sink test02_multi_sink.cpp)
add_executable(sl_test03_stream     test03_stream.cpp)

target_link_libraries(sl_test01_simple     PRIVATE ${USED_LIBS})
target_link_libraries(sl_test02_multi_sink PRIVATE ${USED_LIBS})
target_link_libraries(sl_test03_stream     PRIVATE ${USED_LIBS})
