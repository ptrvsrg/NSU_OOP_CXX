message(STATUS "Creating library \"tuple_utility\"")
add_library(tuple_utility INTERFACE)
target_include_directories(tuple_utility
        INTERFACE include)

message(STATUS "Creating tests for library \"tuple_utility\"")
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

add_executable(tests_tuple_utility
        test/tests_tuple_utility.cpp)
target_link_libraries(tests_tuple_utility
        PUBLIC tuple_utility
        PUBLIC gtest
        PUBLIC gtest_main)
target_compile_options(tests_tuple_utility
        PUBLIC "-Wno-deprecated")
add_test(NAME tests_tuple_utility
        COMMAND tests_tuple_utility
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)