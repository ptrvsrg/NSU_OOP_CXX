message(STATUS "Creating dynamic library of strategy \"random\"")

add_library(random SHARED
        src/random.cpp)
set_target_properties(random PROPERTIES PREFIX "")
target_include_directories(random PUBLIC
        include/random
        ${CMAKE_SOURCE_DIR}/libs/matrix/include/matrix
        ${CMAKE_SOURCE_DIR}/libs/strategy_interface/include/strategy_interface)

link_directories(
        ${CMAKE_BINARY_DIR}/libs/matrix
        ${CMAKE_BINARY_DIR}/libs/strategy_interface)
target_link_libraries(random INTERFACE
        matrix
        strategy_interface)