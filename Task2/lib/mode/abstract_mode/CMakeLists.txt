message(STATUS "Creating library \"abstract_mode\"")

add_library(abstract_mode STATIC
        src/abstract_mode.cpp)
target_include_directories(abstract_mode PUBLIC
        include
        ${CMAKE_SOURCE_DIR}/lib/matrix/include
        ${CMAKE_SOURCE_DIR}/lib/strategies/include)
target_link_directories(abstract_mode PUBLIC
        ${CMAKE_BINARY_DIR}/lib/matrix
        ${CMAKE_BINARY_DIR}/lib/strategy_creator)
target_link_libraries(abstract_mode
        PUBLIC matrix
        PUBLIC strategy_creator)