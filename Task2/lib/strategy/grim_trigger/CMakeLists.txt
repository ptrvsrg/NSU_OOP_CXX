message(STATUS "Creating library of strategy \"grim_trigger\" ")
add_library(grim_trigger STATIC
        src/grim_trigger.cpp)
target_include_directories(grim_trigger PUBLIC
        include
        ../strategy_interface/include)
target_link_directories(grim_trigger
        PUBLIC ${CMAKE_BINARY_DIR}lib/strategy/strategy_interface)
target_link_libraries(grim_trigger
        PUBLIC strategy_interface)

message(STATUS "Creating tests for library of strategy \"grim_trigger\"")

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

add_executable(tests_grim_trigger
        test/tests_grim_trigger.cpp)
target_link_libraries(tests_grim_trigger PUBLIC
        grim_trigger
        gtest
        gtest_main)
add_test(NAME tests_grim_trigger
        COMMAND tests_grim_trigger
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)