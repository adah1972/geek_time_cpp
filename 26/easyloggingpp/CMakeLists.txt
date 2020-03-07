cmake_minimum_required(VERSION 3.10)
project(easyloggingpp_examples)

set(CMAKE_CXX_STANDARD 14)

add_executable(el_test01_simple   test01_simple.cpp  easylogging++.cc)
add_executable(el_test02_unicode  test02_unicode.cpp easylogging++.cc)
add_executable(el_test03_conf     test03_conf.cpp    easylogging++.cc)
add_executable(el_test04_performance_tracking test04_performance_tracking.cpp
               easylogging++.cc)

set_target_properties(el_test02_unicode PROPERTIES COMPILE_FLAGS
                      "-DELPP_UNICODE")
set_target_properties(el_test03_conf PROPERTIES COMPILE_FLAGS
                      "-DELPP_NO_DEFAULT_LOG_FILE")
set_target_properties(el_test04_performance_tracking PROPERTIES COMPILE_FLAGS
                      "-DELPP_NO_DEFAULT_LOG_FILE\
                       -DELPP_FEATURE_PERFORMANCE_TRACKING\
                       -DELPP_PERFORMANCE_MICROSECONDS")

if(UNIX OR APPLE)
add_executable(el_test05_crash_log test05_crash_log.cpp easylogging++.cc)
set_target_properties(el_test05_crash_log PROPERTIES COMPILE_FLAGS
                      "-DELPP_NO_DEFAULT_LOG_FILE\
                       -DELPP_FEATURE_CRASH_LOG")
if(APPLE)
target_link_options(el_test05_crash_log PRIVATE LINKER:-no_pie)
endif(APPLE)
endif(UNIX OR APPLE)
