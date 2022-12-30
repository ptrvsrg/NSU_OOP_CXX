message(STATUS "Creating library \"game\"")

add_library(game STATIC
        src/game.cpp)
target_include_directories(game PUBLIC
        include/game
        ${CMAKE_SOURCE_DIR}/libs/matrix/include/matrix
        ${CMAKE_SOURCE_DIR}/libs/modes/include/mode_creator)
target_link_directories(game PUBLIC
        ${CMAKE_BINARY_DIR}/libs/matrix
        ${CMAKE_BINARY_DIR}/libs/modes)
target_link_libraries(game PUBLIC
        matrix
        mode_creator)

message(STATUS "Creating tests for library \"game\"")

find_package(GTest)
if (NOT GTest_FOUND)
    include(FetchContent)

    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG        release-1.11.0
    )
    FetchContent_MakeAvailable(googletest)
endif ()
add_executable(tests_game
        test/tests_game.cpp)
target_link_libraries(tests_game PUBLIC
        game
        gtest
        gtest_main)
add_test(NAME tests_game
        COMMAND tests_game)