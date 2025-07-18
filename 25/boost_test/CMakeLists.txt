cmake_minimum_required(VERSION 3.10)
project(boost_test_examples)

set(CMAKE_CXX_STANDARD 17)

if(POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()
if(POLICY CMP0144)
  cmake_policy(SET CMP0144 NEW)
endif()

set(Boost_USE_MULTITHREADED OFF)
find_package(Boost REQUIRED unit_test_framework)

include_directories(../../third-party/nvwa)

# The following line is necessary at least on CentOS 7 with Boost 1.67
add_compile_options(-DBOOST_TEST_DYN_LINK)

set(USED_LIBS Boost::unit_test_framework)

add_executable(bt_test01_simple test01_simple.cpp)
add_executable(bt_test02_split  test02_split.cpp test_main.cpp)

target_link_libraries(bt_test01_simple PRIVATE ${USED_LIBS})
target_link_libraries(bt_test02_split  PRIVATE ${USED_LIBS})
