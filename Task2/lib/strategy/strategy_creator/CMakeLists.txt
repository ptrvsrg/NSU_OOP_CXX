message(STATUS "Creating strategy creator")

add_library(strategy_creator STATIC
        src/strategy_creator.cpp)
target_include_directories(strategy_creator PUBLIC
        include
        ../strategy_interface/include
        ${CMAKE_SOURCE_DIR}/libs/matrix/include/matrix)

foreach(STRATEGY_SOURCE_DIR ${STRATEGY_SOURCE_DIRS})
    target_include_directories(strategy_creator 
            PUBLIC ${STRATEGY_SOURCE_DIR}/include)
endforeach(STRATEGY_SOURCE_DIR)

target_link_directories(strategy_creator
        PUBLIC ${STRATEGY_BINARY_DIRS})
target_link_libraries(strategy_creator
        PUBLIC matrix
        PUBLIC ${STRATEGIES}
        INTERFACE strategy_interface)

message(STATUS "Creating tests for library of strategy \"strategy_creator\"")
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

add_executable(tests_strategy_creator
        test/tests_strategy_creator.cpp)
target_link_libraries(tests_strategy_creator PUBLIC
        strategy_creator
        gtest
        gtest_main)
add_test(NAME tests_strategy_creator
        COMMAND tests_strategy_creator
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)