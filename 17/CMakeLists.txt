cmake_minimum_required(VERSION 3.10)
project(functional_examples)

set(CMAKE_CXX_STANDARD 17)

include_directories(../3rd-party/nvwa)

add_executable(fn_test01_count_lines test01_count_lines.cpp)
if(MSVC)
add_executable(fn_test02_par_reduce test02_par_reduce.cpp)
elseif(CMAKE_CXX_COMPILER_ID MATCHES GNU AND
       CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 9)
find_package(Threads)
find_package(TBB)
if(TBB_FOUND)
add_executable(fn_test02_par_reduce test02_par_reduce.cpp)
target_link_libraries(fn_test02_par_reduce PRIVATE TBB::tbb
                      ${CMAKE_THREAD_LIBS_INIT})
endif()
endif()
add_executable(fn_test03_y_combinator test03_y_combinator.cpp)
