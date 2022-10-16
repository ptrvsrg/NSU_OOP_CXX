message(STATUS "Creating library \"abstract_mode\"")


add_library(abstract_mode STATIC
        src/abstract_mode.cpp)
set_target_properties(abstract_mode PROPERTIES PREFIX "")
target_include_directories(abstract_mode PUBLIC
        include/abstract_mode
        ${CMAKE_SOURCE_DIR}/libs/matrix/include/matrix
        ${CMAKE_SOURCE_DIR}/libs/strategy_interface/include/strategy_interface)

link_directories(
        ${CMAKE_BINARY_DIR}/libs/matrix
        ${CMAKE_BINARY_DIR}/libs/strategy_interface)
target_link_libraries(abstract_mode INTERFACE
        abstract_strategy
        matrix)