add_library(ipb_arithmetic STATIC subtract.cpp sum.cpp)

#find_library(IPB_LIB
#            NAMES ipb_arithmetic
#            PATHS ${PROJECT_SOURCE_DIR}/install/lib)   

add_executable(main main.cpp)
target_link_libraries(main ipb_arithmetic)

install(TARGETS ipb_arithmetic DESTINATION ${PROJECT_SOURCE_DIR}/install/lib)