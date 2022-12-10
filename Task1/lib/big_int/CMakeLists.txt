add_library(big_int STATIC
        src/big_int.cpp)
target_include_directories(big_int PUBLIC
        include)
target_link_libraries(big_int PUBLIC
        string_arithmetic)

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

add_executable(tests_big_int
        test/tests_big_int.cpp)
target_link_libraries(tests_big_int
        gtest_main
        big_int)
add_test(NAME tests_big_int
        COMMAND tests_big_int
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)