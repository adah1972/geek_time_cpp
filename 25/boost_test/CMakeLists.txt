cmake_minimum_required(VERSION 3.13)
project(boost_test_examples)

set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_MULTITHREADED OFF)
find_package(Boost REQUIRED unit_test_framework)

include_directories(${PROJECT_SOURCE_DIR}/../../3rd-party/nvwa)

# The following line is necessary at least on CentOS 7 with Boost 1.67
add_compile_options(-DBOOST_TEST_DYN_LINK)

set(USED_LIBS Boost::unit_test_framework)

add_executable(bt_test01_simple bt_test01_simple.cpp)
add_executable(bt_test02_split  bt_test02_split.cpp bt_test_main.cpp)

target_link_libraries(bt_test01_simple PRIVATE ${USED_LIBS})
target_link_libraries(bt_test02_split  PRIVATE ${USED_LIBS})
