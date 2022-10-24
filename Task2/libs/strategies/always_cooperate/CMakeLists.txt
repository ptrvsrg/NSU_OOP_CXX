message(STATUS "Creating library of strategy \"always_cooperate\" ")

add_library(always_cooperate STATIC
        src/always_cooperate.cpp)
target_include_directories(always_cooperate PUBLIC
        include/always_cooperate
        ${CMAKE_SOURCE_DIR}/libs/strategies/strategy_creator/include/strategy_creator
        ${CMAKE_SOURCE_DIR}/libs/strategies/strategy_interface/include/strategy_interface)
target_link_directories(always_cooperate PUBLIC
        ${CMAKE_BINARY_DIR}/libs/strategies/strategy_creator
        ${CMAKE_BINARY_DIR}/libs/strategies/strategy_interface)
target_link_libraries(always_cooperate
        PUBLIC strategy_creator
        INTERFACE strategy_interface)