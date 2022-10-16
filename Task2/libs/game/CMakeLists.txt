message(STATUS "Creating library \"game\"")


add_library(game STATIC
        src/game.cpp)
set_target_properties(game PROPERTIES PREFIX "")
target_include_directories(game PUBLIC
        include/game
        ${CMAKE_SOURCE_DIR}/libs/matrix/include/matrix
        ${CMAKE_SOURCE_DIR}/libs/modes/detailed_mode/include/detailed_mode
        ${CMAKE_SOURCE_DIR}/libs/modes/fast_mode/include/fast_mode
        ${CMAKE_SOURCE_DIR}/libs/modes/tournament_mode/include/tournament_mode)

link_directories(${CMAKE_BINARY_DIR}/libs/matrix
        ${CMAKE_BINARY_DIR}/libs/modes/detailed_mode
        ${CMAKE_BINARY_DIR}/libs/modes/fast_mode
        ${CMAKE_BINARY_DIR}/libs/modes/tournament_mode)
target_link_libraries(game PUBLIC
        matrix
        detailed_mode
        fast_mode
        tournament_mode)