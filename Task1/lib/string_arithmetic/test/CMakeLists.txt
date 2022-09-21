set(TEST_PROJECT_NAME string_arithmetic_tests)
set(LIBRARY_TESTS_SOURCE tests_string_arithmetic.cpp)

project(${TEST_PROJECT_NAME} CXX)

enable_testing()

if (NOT (TARGET gtest AND TARGET gtest_main))
    message(FATAL_ERROR "gtest and gtest_main targets NOT found")
endif()

add_executable(${TEST_PROJECT_NAME} ${LIBRARY_TESTS_SOURCE})
target_link_libraries(${TEST_PROJECT_NAME} gtest gtest_main ${LIBRARY_NAME})

add_test(${TEST_PROJECT_NAME} ${TEST_PROJECT_NAME})