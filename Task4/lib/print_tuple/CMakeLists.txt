message(STATUS "Creating library \"print_tuple\"")
add_library(print_tuple INTERFACE)
target_include_directories(print_tuple
        INTERFACE include)

message(STATUS "Creating tests for library \"print_tuple\"")
find_package(GTest REQUIRED)
add_executable(tests_print_tuple
        test/tests_print_tuple.cpp)
target_link_libraries(tests_print_tuple
        PUBLIC print_tuple
        PUBLIC gtest
        PUBLIC gtest_main)
target_compile_options(tests_print_tuple
        PUBLIC "-Wno-deprecated")
add_test(NAME tests_print_tuple
        COMMAND tests_print_tuple
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)