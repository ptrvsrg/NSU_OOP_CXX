message(STATUS "Creating library \"cl_parser\"")

set(CONVERTERS_CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/config/converters_desc.json")
configure_file(include/cl_parser.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/include/cl_parser.h)

find_package(Boost
        COMPONENTS container program_options
        REQUIRED)
add_library(cl_parser STATIC
        src/cl_parser.cpp
        src/cl_parser_errors.cpp)
target_include_directories(cl_parser
        PUBLIC include
        PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include
        PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(cl_parser
        PUBLIC ${Boost_LIBRARIES})
target_compile_definitions(cl_parser
        PUBLIC -DBOOST_BIND_GLOBAL_PLACEHOLDERS)

message(STATUS "Creating tests for library \"cl_parser\"")

find_package(GTest REQUIRED)
add_executable(tests_cl_parser
        test/tests_cl_parser.cpp)
target_include_directories(cl_parser
        PUBLIC include)
target_link_libraries(tests_cl_parser
        PUBLIC cl_parser
        PUBLIC gtest
        PUBLIC gtest_main)
add_test(NAME tests_cl_parser
        COMMAND tests_cl_parser
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)