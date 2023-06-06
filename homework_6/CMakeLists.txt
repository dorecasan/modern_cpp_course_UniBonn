cmake_minimum_required(VERSION 3.8)
project(homework_6)


set(TOAN_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(TOAN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

include_directories(${TOAN_INSTALL_INCLUDE_DIR})
include_directories(${TOAN_SOURCE_DIR})

add_library(image src/image.cpp)
add_library(io_tools io_tools/io_tools.cpp)

add_subdirectory(tests)