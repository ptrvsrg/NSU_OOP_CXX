message(STATUS "Creating library \"matrix\"")

add_library(matrix STATIC
        src/matrix.cpp)
target_include_directories(matrix PUBLIC
        include/matrix
        ${CMAKE_SOURCE_DIR}/libs/strategies/include/strategy_interface)
target_link_directories(matrix PUBLIC
        ${CMAKE_BINARY_DIR}/strategies/libs/strategy_interface)
target_link_libraries(matrix INTERFACE
        strategy_interface)

message(STATUS "Creating tests for library \"matrix\"")

enable_testing()
find_package(GTest REQUIRED)
add_executable(tests_matrix
        test/tests_matrix.cpp)
target_link_libraries(tests_matrix PUBLIC
        matrix
        gtest
        gtest_main)