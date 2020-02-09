cmake_minimum_required(VERSION 3.13)
project(coroutines_ts_example)

if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
  if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
        /std:c++latest\
        -fms-compatibility -Xclang -fcoroutines-ts")
  elseif(UNIX OR APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
        -std=c++17 -stdlib=libc++\
        -fcoroutines-ts")
  endif()

elseif(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
      -std=c++17\
      -fcoroutines -fconcepts")

elseif(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
      /std:c++latest /await")

else()
  message(FATAL_ERROR "Unrecognized compiler")

endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${PROJECT_SOURCE_DIR}/../../3rd-party/cppcoro/include")

add_executable(fibonacci_cppcoro_generator fibonacci_cppcoro_generator.cpp)
