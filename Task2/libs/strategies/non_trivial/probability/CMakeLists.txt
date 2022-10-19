message(STATUS "Creating dynamic library of strategy \"probability\"")

add_library(probability SHARED
        src/probability.cpp)
set_target_properties(probability PROPERTIES PREFIX "")
target_include_directories(probability PUBLIC
        include/probability
        ${CMAKE_SOURCE_DIR}/libs/matrix/include/matrix
        ${CMAKE_SOURCE_DIR}/libs/strategy_interface/include/strategy_interface)

link_directories(
        ${CMAKE_BINARY_DIR}/libs/matrix
        ${CMAKE_BINARY_DIR}/libs/strategy_interface)
target_link_libraries(probability
        PUBLIC matrix
        INTERFACE strategy_interface)


enable_testing()
find_package(GTest REQUIRED)

add_executable(tests_probability
        test/tests_probability.cpp)
target_link_libraries(tests_probability PUBLIC
        probability
        gtest
        gtest_main)