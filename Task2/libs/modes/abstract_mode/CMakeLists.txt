message(STATUS "Creating library \"abstract_mode\"")

add_library(abstract_mode STATIC
        src/abstract_mode.cpp)
target_include_directories(abstract_mode PUBLIC
        include/abstract_mode
        ${CMAKE_SOURCE_DIR}/libs/matrix/include/matrix
        ${CMAKE_SOURCE_DIR}/libs/strategy_creator/include/strategy_creator
        ${CMAKE_SOURCE_DIR}/libs/strategy_interface/include/strategy_interface)
target_link_directories(abstract_mode PUBLIC
        ${CMAKE_BINARY_DIR}/libs/matrix
        ${CMAKE_BINARY_DIR}/libs/strategy_creator
        ${CMAKE_BINARY_DIR}/libs/strategy_interface)
target_link_libraries(abstract_mode
        PUBLIC matrix
        PUBLIC strategy_creator
        INTERFACE strategy_interface)