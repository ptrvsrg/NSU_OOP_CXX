message(STATUS "Creating converter library \"mix\"")

add_library(mix STATIC
        src/mix.cpp)
target_include_directories(mix
        PUBLIC include
        PUBLIC ../converter_interface/include
        PUBLIC ../converter_errors/include)
target_link_directories(mix
        PUBLIC ${CMAKE_BINARY_DIR}/lib/converter/converter_interface)
target_link_libraries(mix
        PUBLIC converter_interface
        PUBLIC converter_errors)

message(STATUS "Creating tests for converter library \"mix\"")

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
add_executable(tests_mix
        test/tests_mix.cpp)
target_link_libraries(tests_mix
        PUBLIC mix
        PUBLIC gtest
        PUBLIC gtest_main)
add_test(NAME tests_mix
        COMMAND tests_mix
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)