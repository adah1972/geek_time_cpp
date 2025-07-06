# libcxxdetect.cmake - Detection module for libc++ and its version
#
# Usage:
#   include(libcxxdetect.cmake)
#   detect_libcxx()
#
#   if(LIBCXX_FOUND)
#     message(STATUS "Using libc++ version ${LIBCXX_VERSION}")
#     if(LIBCXX_VERSION VERSION_GREATER_EQUAL 18.0)
#       # Handle newer libc++ features...
#     endif()
#   endif()

# Avoid multiple includes
if(DEFINED LIBCXX_DETECT_INCLUDED)
  return()
endif()
set(LIBCXX_DETECT_INCLUDED TRUE)

include(CheckCXXSourceCompiles)
include(CheckCXXSourceRuns)

# Internal detection function
function(detect_libcxx_impl)
  # Check if libc++ is being used
  check_cxx_source_compiles("
    #include <ciso646>
    #ifdef _LIBCPP_VERSION
    int main() {}
    #else
    #error Not using libc++
    #endif
  " USING_LIBCXX)

  # Set default values
  set(LIBCXX_FOUND FALSE PARENT_SCOPE)
  set(LIBCXX_VERSION "0.0.0" PARENT_SCOPE)
  set(LIBCXX_VERSION_MAJOR 0 PARENT_SCOPE)
  set(LIBCXX_VERSION_MINOR 0 PARENT_SCOPE)
  set(LIBCXX_VERSION_PATCH 0 PARENT_SCOPE)
  set(LIBCXX_RAW_VERSION 0 PARENT_SCOPE)

  # If libc++ is found, get its version
  if(USING_LIBCXX)
    # Extract libc++ version information
    file(WRITE "${CMAKE_BINARY_DIR}/libcxx_version_detect.cpp" "
      #include <ciso646>
      #include <iostream>

      int main() {
        std::cout << _LIBCPP_VERSION;
      }
    ")

    try_run(
      RUN_RESULT COMPILE_RESULT
      ${CMAKE_BINARY_DIR}
      ${CMAKE_BINARY_DIR}/libcxx_version_detect.cpp
      RUN_OUTPUT_VARIABLE LIBCXX_RAW_VERSION
    )

    if(COMPILE_RESULT AND RUN_RESULT EQUAL 0)
      set(LIBCXX_FOUND TRUE PARENT_SCOPE)
      set(LIBCXX_RAW_VERSION ${LIBCXX_RAW_VERSION} PARENT_SCOPE)

      # Parse version based on the official format
      string(LENGTH "${LIBCXX_RAW_VERSION}" VERSION_LENGTH)

      # Currently the version number can have the following formats:
      #   XYZZ
      #   XXYZZ
      #   XXYYZZ
      #
      # So we parse from right, and the minor version (Y) can have one
      # or two digits.
      math(EXPR LAST_TWO_INDEX "${VERSION_LENGTH} - 2")
      if(VERSION_LENGTH LESS 4)
        message(WARNING "Unrecognized libc++ version \"${LIBCXX_RAW_VERSION}\" encountered")
        return()
      elseif(VERSION_LENGTH LESS 6)
        set(MINOR_LEN 1)
      else()
        set(MINOR_LEN 2)
      endif()
      math(EXPR MINOR_INDEX "${LAST_TWO_INDEX} - ${MINOR_LEN}")

      string(SUBSTRING "${LIBCXX_RAW_VERSION}" ${LAST_TWO_INDEX} 2 LIBCXX_VERSION_PATCH)
      string(SUBSTRING "${LIBCXX_RAW_VERSION}" ${MINOR_INDEX} ${MINOR_LEN} LIBCXX_VERSION_MINOR)
      string(SUBSTRING "${LIBCXX_RAW_VERSION}" 0 ${MINOR_INDEX} LIBCXX_VERSION_MAJOR)

      # Remove leading zeros but keep at least one digit
      string(REGEX REPLACE "^0+([0-9])" "\\1" LIBCXX_VERSION_MAJOR "${LIBCXX_VERSION_MAJOR}")
      string(REGEX REPLACE "^0+([0-9])" "\\1" LIBCXX_VERSION_MINOR "${LIBCXX_VERSION_MINOR}")
      string(REGEX REPLACE "^0+([0-9])" "\\1" LIBCXX_VERSION_PATCH "${LIBCXX_VERSION_PATCH}")

      # Set parsed version components
      set(LIBCXX_VERSION_MAJOR ${LIBCXX_VERSION_MAJOR} PARENT_SCOPE)
      set(LIBCXX_VERSION_MINOR ${LIBCXX_VERSION_MINOR} PARENT_SCOPE)
      set(LIBCXX_VERSION_PATCH ${LIBCXX_VERSION_PATCH} PARENT_SCOPE)

      # Set full version string
      set(LIBCXX_VERSION "${LIBCXX_VERSION_MAJOR}.${LIBCXX_VERSION_MINOR}.${LIBCXX_VERSION_PATCH}" PARENT_SCOPE)

      # Log detection
      message(STATUS "libc++ detected - version: ${LIBCXX_VERSION_MAJOR}.${LIBCXX_VERSION_MINOR}.${LIBCXX_VERSION_PATCH} (raw: ${LIBCXX_RAW_VERSION})")

    else()
      message(WARNING "libc++ detected but failed to determine version")
    endif()
  else()
    message(STATUS "libc++ not detected")
  endif()
endfunction()

# Main detection function
function(detect_libcxx)
  if(DEFINED LIBCXX_FOUND)
    return()
  endif()
  detect_libcxx_impl()
  set(LIBCXX_FOUND ${LIBCXX_FOUND} CACHE BOOL "Whether libc++ is found")
  set(LIBCXX_VERSION ${LIBCXX_VERSION} CACHE STRING "libc++ version")
  set(LIBCXX_VERSION_MAJOR ${LIBCXX_VERSION_MAJOR} CACHE STRING "libc++ version major")
  set(LIBCXX_VERSION_MINOR ${LIBCXX_VERSION_MINOR} CACHE STRING "libc++ version minor")
  set(LIBCXX_VERSION_PATCH ${LIBCXX_VERSION_PATCH} CACHE STRING "libc++ version patch")
  set(LIBCXX_RAW_VERSION ${LIBCXX_RAW_VERSION} CACHE STRING "libc++ raw version string")
endfunction()
