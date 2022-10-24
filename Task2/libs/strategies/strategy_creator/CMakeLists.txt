message(STATUS "Creating library \"strategy_creator\"")

add_library(strategy_creator STATIC
        src/strategy_creator.cpp)
target_include_directories(strategy_creator PUBLIC
        include/strategy_creator
        ${CMAKE_SOURCE_DIR}/libs/matrix/include/matrix
        ${CMAKE_SOURCE_DIR}/libs/strategies/strategy_interface/include/strategy_interface)
target_link_directories(strategy_creator PUBLIC
        ${CMAKE_BINARY_DIR}/libs/matrix
        ${CMAKE_BINARY_DIR}/libs/strategies/strategy_interface)

foreach(STRATEGY ${STRATEGIES})
    target_include_directories(strategy_creator PUBLIC
            ${CMAKE_SOURCE_DIR}/libs/strategies/${STRATEGY}/include/${STRATEGY})
    target_link_directories(strategy_creator PUBLIC
            ${CMAKE_BINARY_DIR}/libs/strategies/${STRATEGY})
endforeach(STRATEGY)

target_link_libraries(strategy_creator
        PUBLIC matrix
        PUBLIC ${STRATEGIES}
        INTERFACE strategy_interface)