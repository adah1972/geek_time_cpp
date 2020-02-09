cmake_minimum_required(VERSION 3.13)
project(range_examples)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
      -std=c++17 -fconcepts")
elseif(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
      /std:c++latest /permissive-")
else()
  message(FATAL_ERROR "Unrecognized compiler")
endif()

find_package(Armadillo CONFIG)
if(Armadillo_FOUND)
  set(HAVE_ARMA 1)
endif()
if(HAVE_ARMA)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_ARMA")
endif()

include_directories(${PROJECT_SOURCE_DIR}/../3rd-party/cmcstl2/include)
include_directories(${PROJECT_SOURCE_DIR}/../common)

add_executable(test01_integral_concept test01_integral_concept.cpp)
add_executable(test02_concepts         test02_concepts.cpp)
add_executable(test03_concept_fail     test03_concept_fail.cpp)
add_executable(test04_range_concept    test04_range_concept.cpp)

if(HAVE_ARMA)
  target_link_libraries(test02_concepts PRIVATE ${ARMADILLO_LIBRARIES})
endif()
