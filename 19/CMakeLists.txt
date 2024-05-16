cmake_minimum_required(VERSION 3.10)
project(thread_examples)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads)

include_directories(../common)

add_executable(thrd_test01_thread        test01_thread.cpp)
add_executable(thrd_test02_cond_var      test02_cond_var.cpp)
add_executable(thrd_test03_async         test03_async.cpp)
add_executable(thrd_test04_promise       test04_promise.cpp)
add_executable(thrd_test05_packaged_task test05_packaged_task.cpp)

target_link_libraries(thrd_test01_thread        ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(thrd_test02_cond_var      ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(thrd_test03_async         ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(thrd_test04_promise       ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(thrd_test05_packaged_task ${CMAKE_THREAD_LIBS_INIT})
