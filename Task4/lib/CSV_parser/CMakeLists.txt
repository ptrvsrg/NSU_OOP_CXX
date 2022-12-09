message(STATUS "Creating library \"CSV_parser\"")

add_library(CSV_parser STATIC
        src/CSV_parser_errors.cpp)
target_include_directories(CSV_parser
        PUBLIC include
        INTERFACE ${CMAKE_SOURCE_DIR}/lib/tuple_utility/include)

message(STATUS "Creating tests for library \"CSV_parser\"")
find_package(GTest)
if (NOT GTest_FOUND)
    include(FetchContent)

    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG        release-1.11.0
    )
    FetchContent_MakeAvailable(googletest)
endif (GTest_FOUND)

add_executable(tests_CSV_parser
        test/tests_CSV_parser.cpp)
target_link_libraries(tests_CSV_parser
        PUBLIC CSV_parser
        PUBLIC gtest
        PUBLIC gtest_main)
target_compile_options(tests_CSV_parser
        PUBLIC "-Wno-deprecated")
add_test(NAME tests_CSV_parser
        COMMAND tests_CSV_parser
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)