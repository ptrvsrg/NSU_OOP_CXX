message(STATUS "Creating library \"config_parser\"")

add_library(config_parser STATIC
        src/config_parser.cpp
        src/config_parser_errors.cpp)
target_include_directories(config_parser
        PUBLIC include/config_parser)

message(STATUS "Creating tests for library \"config_parser\"")

enable_testing()
find_package(GTest REQUIRED)
add_executable(tests_config_parser
        test/tests_config_parser.cpp)
target_include_directories(tests_config_parser
        PUBLIC include/config_parser)
target_link_libraries(tests_config_parser
        PUBLIC config_parser
        PUBLIC gtest
        PUBLIC gtest_main)