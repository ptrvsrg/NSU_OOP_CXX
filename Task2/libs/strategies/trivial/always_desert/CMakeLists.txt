message(STATUS "Creating dynamic library of strategy \"always_desert\"")

add_library(always_desert SHARED
        src/always_desert.cpp)
set_target_properties(always_desert PROPERTIES PREFIX "")
target_include_directories(always_desert PUBLIC
        include/always_desert
        ${CMAKE_SOURCE_DIR}/libs/matrix/include/matrix
        ${CMAKE_SOURCE_DIR}/libs/strategy_interface/include/strategy_interface)

link_directories(
        ${CMAKE_BINARY_DIR}/libs/matrix
        ${CMAKE_BINARY_DIR}/libs/strategy_interface)
target_link_libraries(always_desert INTERFACE
        matrix
        strategy_interface)