cmake_minimum_required(VERSION 2.8.3)
project(task_2)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/results/lib)
# set executables folder
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/results/bin)

include_directories(
    ${PROJECT_SOURCE_DIR}/include    
)
# Installing Directories
install(DIRECTORY include/ DESTINATION ${PROJECT_SOURCE_DIR}/install/include)

add_subdirectory(src)
