add_library(string_arithmetic STATIC
        src/string_arithmetic.cpp)
target_include_directories(string_arithmetic PUBLIC
        include)

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

add_executable(tests_string_arithmetic
        test/tests_string_arithmetic.cpp)
target_link_libraries(tests_string_arithmetic
        gtest_main
        string_arithmetic)
add_test(NAME tests_string_arithmetic
        COMMAND tests_string_arithmetic
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)