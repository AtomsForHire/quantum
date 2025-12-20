cmake_minimum_required(VERSION 3.12)
project(ccc C)

add_executable(ccc ./src/main.c)

get_filename_component(dirname ${CMAKE_BINARY_DIR} NAME)
if (${dirname} MATCHES "dbg" OR ${dirname} MATCHES "debug")
    set(CMAKE_BUILD_TYPE Debug)
else()
    set(CMAKE_BUILD_TYPE Release)
endif()

install(TARGETS ccc DESTINATION bin)
