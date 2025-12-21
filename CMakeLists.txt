cmake_minimum_required(VERSION 3.12)
project(ccc C)

add_executable(ccc ./src/main.c)

# Find LAPACK library
set(BLA_VENDOR "Generic")
find_package(LAPACK REQUIRED)
if (APPLE)
    message(STATUS "INFO: Building for Apple system")
    find_path(LAPACKE_INCLUDE_DIR NAMES lapacke.h HINTS /opt/homebrew/opt/lapack/)
    find_library(LAPACKE_LIBRARY NAMES lapacke HINTS /opt/homebrew/)
elseif(UNIX)
    message(STATUS "INFO: Building for UNIX system")
    find_path(LAPACKE_INCLUDE_DIR lapacke.h HINTS)
    find_library(LAPACKE_LIBRARY NAMES lapacke HINTS)
endif()

if(NOT LAPACKE_INCLUDE_DIR OR NOT LAPACKE_LIBRARY)
    message(FATAL_ERROR "Could not find LAPACKE")
endif()

get_filename_component(dirname ${CMAKE_BINARY_DIR} NAME)
if (${dirname} MATCHES "dbg" OR ${dirname} MATCHES "debug")
    set(CMAKE_BUILD_TYPE Debug)
else()
    set(CMAKE_BUILD_TYPE Release)
endif()

install(TARGETS ccc DESTINATION bin)
