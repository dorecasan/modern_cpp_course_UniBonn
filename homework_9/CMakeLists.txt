cmake_minimum_required(VERSION 3.8)
project(homework_9)

#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")
find_package(OpenCV 4.1 REQUIRED)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

set(TOAN_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(TOAN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

include_directories(${TOAN_INSTALL_INCLUDE_DIR})
include_directories(${TOAN_SOURCE_DIR})

add_library(kmeans src/kmeans.cpp)
add_library(bow_dictionary src/bow_dictionary.cpp)
add_library(histogram src/histogram.cpp)

target_link_libraries(kmeans ${OpenCV_LIBRARIES})
target_link_libraries(bow_dictionary ${OpenCV_LIBRARIES} kmeans)
target_link_libraries(histogram ${OpenCV_LIBRARIES} bow_dictionary)

enable_testing ()
add_subdirectory(tests)
