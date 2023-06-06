cmake_minimum_required(VERSION 3.8)
project(bow_dictionary)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")
find_package(OpenCV 4.1 REQUIRED)


set(TOAN_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(TOAN_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

include_directories(${TOAN_INSTALL_INCLUDE_DIR})
include_directories(${TOAN_SOURCE_DIR})

add_library(serialization  src/convert_dataset.cpp src/serialize.cpp)
add_library(kmeans src/kmeans.cpp)
add_library(bow_dictionary src/bow_dictionary.cpp)

target_link_libraries(kmeans ${OpenCV_LIBRARIES})
target_link_libraries(serialization ${OpenCV_LIBRARIES} stdc++fs)
target_link_libraries(bow_dictionary ${OpenCV_LIBRARIES} kmeans)

add_executable(test_toan tests/test_toan.cpp)
target_link_libraries(test_toan ${OpenCV_LIBRARIES})

add_subdirectory(tests)
