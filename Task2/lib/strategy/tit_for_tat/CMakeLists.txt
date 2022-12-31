message(STATUS "Creating library of strategy \"tit_for_tat\" ")
add_library(tit_for_tat STATIC
        src/tit_for_tat.cpp)
target_include_directories(tit_for_tat PUBLIC
        include
        ../strategy_interface/include)
target_link_directories(tit_for_tat
        PUBLIC ${CMAKE_BINARY_DIR}lib/strategy/strategy_interface)
target_link_libraries(tit_for_tat
        PUBLIC strategy_interface)

message(STATUS "Creating tests for library of strategy \"tit_for_tat\"")

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

add_executable(tests_tit_for_tat
        test/tests_tit_for_tat.cpp)
target_link_libraries(tests_tit_for_tat PUBLIC
        tit_for_tat
        gtest
        gtest_main)
add_test(NAME tests_tit_for_tat
        COMMAND tests_tit_for_tat
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)