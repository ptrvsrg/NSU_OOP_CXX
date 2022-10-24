message(STATUS "Creating library \"fast_mode\"")

add_library(fast_mode STATIC
        src/fast_mode.cpp)
target_include_directories(fast_mode PUBLIC
        include/fast_mode
        ${CMAKE_SOURCE_DIR}/libs/abstract_mode/include/abstract_mode)
target_link_directories(fast_mode PUBLIC
        ${CMAKE_BINARY_DIR}/libs/abstract_mode)
target_link_libraries(fast_mode PUBLIC
        abstract_mode)