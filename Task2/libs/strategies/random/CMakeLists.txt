message(STATUS "Creating library of strategy \"random\"")

add_library(random STATIC
        src/random.cpp)
target_include_directories(random PUBLIC
        include/random
        ${CMAKE_SOURCE_DIR}/libs/matrix/include/matrix
        ${CMAKE_SOURCE_DIR}/libs/strategies/strategy_interface/include/strategy_interface)
target_link_directories(random PUBLIC
        ${CMAKE_BINARY_DIR}/libs/matrix
        ${CMAKE_BINARY_DIR}/libs/strategies/strategy_interface)
target_link_libraries(random
        PUBLIC matrix
        INTERFACE strategy_interface)