cmake_minimum_required(VERSION 3.21)
project(GBSTL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

add_library(linked_list STATIC
        "include/linked_list.h"
        "source/linked_list.cpp")

target_include_directories(linked_list PUBLIC "include")

add_executable(test
        "test/test.cpp")
target_link_libraries(test PUBLIC linked_list)