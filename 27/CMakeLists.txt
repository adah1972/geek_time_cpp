cmake_minimum_required(VERSION 3.13)
project(cpprestsdk_examples)

set(CMAKE_CXX_STANDARD 17)
set(Boost_USE_MULTITHREADED ON)

find_package(cpprestsdk CONFIG REQUIRED)
find_package(Threads)
find_package(Boost REQUIRED chrono system thread)

if(WIN32)
  # CMake on Windows with vcpkg
  set(USED_LIBS
    cpprestsdk::cpprest
    cpprestsdk::cpprestsdk_zlib_internal
    cpprestsdk::cpprestsdk_boost_internal
    cpprestsdk::cpprestsdk_brotli_internal)
else(WIN32)
  # Linux and macOS
  set(USED_LIBS
    cpprest
    cpprestsdk::cpprestsdk_openssl_internal
    Boost::chrono
    Boost::system
    Boost::thread
    Threads::Threads)
endif(WIN32)

add_executable(client      client.cpp)
add_executable(client_save client_save.cpp)
add_executable(server      server.cpp)
add_executable(test_json   test_json.cpp)

target_link_libraries(client      PRIVATE ${USED_LIBS})
target_link_libraries(client_save PRIVATE ${USED_LIBS})
target_link_libraries(server      PRIVATE ${USED_LIBS})
target_link_libraries(test_json   PRIVATE ${USED_LIBS})
