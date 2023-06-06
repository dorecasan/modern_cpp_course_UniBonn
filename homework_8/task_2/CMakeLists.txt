cmake_minimum_required(VERSION 3.8)
project(homework_8)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")
find_package(OpenCV 4.1 REQUIRED)
find_package(PNG REQUIRED)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(TOAN_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(TOAN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

include_directories(${TOAN_INSTALL_INCLUDE_DIR})
#include_directories(${TOAN_SOURCE_DIR})
include_directories(${PNG_INCLUDE_DIR})

add_library(io_stragety src/ppm_io_stragety.cpp src/png_io_stragety.cpp)
target_link_libraries(io_stragety ${PNG_LIBRARY})

add_library(image src/image_class.cpp)
target_link_libraries(image io_stragety ${OpenCV_LIBRARIES})

add_subdirectory(tests)
