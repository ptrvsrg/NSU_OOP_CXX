message(STATUS "Creating library \"WAV\"")

add_library(WAV STATIC
        src/WAV_errors.cpp
        src/WAV_reader.cpp
        src/WAV_writer.cpp)
target_include_directories(WAV
        PUBLIC include)

message(STATUS "Creating tests for library \"WAV\"")

find_package(GTest REQUIRED)
add_executable(tests_WAV
        test/tests_WAV.cpp)
target_link_libraries(tests_WAV
        PUBLIC WAV
        PUBLIC gtest
        PUBLIC gtest_main)
add_test(NAME tests_WAV
        COMMAND tests_WAV
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)