cmake_minimum_required(VERSION 3.21)
project(GBTL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../test_scripts)

add_executable(${PROJECT_NAME}
        test_scripts/main.cpp
        include/linked_list.h)
target_include_directories(${PROJECT_NAME} PUBLIC include)
