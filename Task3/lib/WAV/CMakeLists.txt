message(STATUS "Creating library \"WAV\"")

add_library(WAV STATIC
        src/WAV_errors.cpp
        src/WAV_reader.cpp
        src/WAV_writer.cpp)
target_include_directories(WAV
        PUBLIC include
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/iostream_errors/include)
target_link_directories(WAV
        PUBLIC ${CMAKE_BINARY_DIR}/lib/iostream_errors)
target_link_libraries(WAV
        PUBLIC iostream_errors)

message(STATUS "Creating tests for library \"WAV\"")

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
add_executable(tests_WAV
        test/tests_WAV.cpp)
target_link_libraries(tests_WAV
        PUBLIC WAV
        PUBLIC gtest
        PUBLIC gtest_main)
add_test(NAME tests_WAV
        COMMAND tests_WAV
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)