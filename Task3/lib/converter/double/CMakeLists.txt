message(STATUS "Creating converter library \"double\"")

add_library(double STATIC
        src/double.cpp)
target_include_directories(double
        PUBLIC include
        PUBLIC ../converter_interface/include
        PUBLIC ../converter_errors/include)
target_link_directories(double
        PUBLIC ${CMAKE_BINARY_DIR}/lib/converter/converter_interface)
target_link_libraries(double
        PUBLIC converter_interface
        PUBLIC converter_errors)

message(STATUS "Creating tests for converter library \"double\"")

find_package(GTest REQUIRED)
add_executable(tests_double
        test/tests_double.cpp)
target_link_libraries(tests_double
        PUBLIC double
        PUBLIC gtest
        PUBLIC gtest_main)
add_test(NAME tests_double
        COMMAND tests_double
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)