message(STATUS "Creating library \"CSV_parser\"")
add_library(CSV_parser INTERFACE)
target_include_directories(CSV_parser
        INTERFACE include
        INTERFACE ${CMAKE_SOURCE_DIR}/lib/tuple_utility/include)

message(STATUS "Creating tests for library \"CSV_parser\"")
find_package(GTest REQUIRED)
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