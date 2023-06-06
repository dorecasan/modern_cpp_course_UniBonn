cmake_minimum_required(VERSION 3.8)
project(homework_5)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")



set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(TOAN_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(TOAN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

include_directories(${TOAN_INSTALL_INCLUDE_DIR})
include_directories(${TOAN_SOURCE_DIR})

enable_testing()
add_subdirectory(tests)
