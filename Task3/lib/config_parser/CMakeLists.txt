message(STATUS "Creating library \"config_parser\"")

add_library(config_parser STATIC
        src/config_parser.cpp)
target_include_directories(config_parser
        PUBLIC include
        PUBLIC ${CMAKE_SOURCE_DIR}/lib/iostream_errors/include)
target_link_directories(config_parser
        PUBLIC ${CMAKE_BINARY_DIR}/lib/iostream_errors)
target_link_libraries(config_parser
        PUBLIC iostream_errors)

message(STATUS "Creating tests for library \"config_parser\"")

find_package(GTest REQUIRED)
add_executable(tests_config_parser
        test/tests_config_parser.cpp)
target_link_libraries(tests_config_parser
        PUBLIC config_parser
        PUBLIC gtest
        PUBLIC gtest_main)
add_test(NAME tests_config_parser
        COMMAND tests_config_parser
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)