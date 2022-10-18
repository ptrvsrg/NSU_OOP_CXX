message(STATUS "Creating library \"matrix\"")


add_library(matrix STATIC
        src/matrix.cpp)
set_target_properties(matrix PROPERTIES PREFIX "")
target_include_directories(matrix PUBLIC
        include/matrix
        ${CMAKE_SOURCE_DIR}/libs/strategy_interface/include/strategy_interface)

link_directories(${CMAKE_BINARY_DIR}/libs/strategy_interface)
target_link_libraries(matrix INTERFACE
        strategy_interface)