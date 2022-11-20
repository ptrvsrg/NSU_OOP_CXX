message(STATUS "Creating library \"cl_parser\"")

find_package(Boost COMPONENTS program_options REQUIRED)
add_library(cl_parser STATIC
        src/cl_parser.cpp
        src/cl_parser_errors.cpp)
target_include_directories(cl_parser
        PUBLIC include/cl_parser
        PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(cl_parser
        PUBLIC ${Boost_LIBRARIES})

message(STATUS "Creating tests for library \"cl_parser\"")

enable_testing()
find_package(GTest REQUIRED)
add_executable(tests_cl_parser
        test/tests_cl_parser.cpp)
target_include_directories(cl_parser
        PUBLIC include/cl_parser)
target_link_libraries(tests_cl_parser
        PUBLIC cl_parser
        PUBLIC gtest
        PUBLIC gtest_main)
add_test(NAME tests_cl_parser
        COMMAND tests_cl_parser
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)