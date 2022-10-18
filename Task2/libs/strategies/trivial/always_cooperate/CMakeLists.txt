message(STATUS "Creating dynamic library of strategy \"always_cooperate\" ")

add_library(always_cooperate SHARED
        src/always_cooperate.cpp)
set_target_properties(always_cooperate PROPERTIES PREFIX "")
target_include_directories(always_cooperate PUBLIC
        include/always_cooperate
        ${CMAKE_SOURCE_DIR}/libs/matrix/include/matrix
        ${CMAKE_SOURCE_DIR}/libs/strategy_interface/include/strategy_interface)

link_directories(
        ${CMAKE_BINARY_DIR}/libs/matrix
        ${CMAKE_BINARY_DIR}/libs/strategy_interface)
target_link_libraries(always_cooperate INTERFACE
        matrix
        strategy_interface)