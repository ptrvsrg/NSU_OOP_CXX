message(STATUS "Creating library \"game\"")

add_library(game STATIC
        src/game.cpp)
target_include_directories(game PUBLIC
        include/game
        ${CMAKE_SOURCE_DIR}/libs/matrix/include/matrix
        ${CMAKE_SOURCE_DIR}/libs/modes/mode_creator/include/mode_creator)
target_link_directories(game PUBLIC
        ${CMAKE_BINARY_DIR}/libs/matrix
        ${CMAKE_BINARY_DIR}/libs/modes/mode_creator)
target_link_libraries(game PUBLIC
        matrix
        mode_creator)

enable_testing()
find_package(GTest REQUIRED)
add_executable(tests_game
        test/tests_game.cpp)
target_link_libraries(tests_game PUBLIC
        game
        gtest
        gtest_main)