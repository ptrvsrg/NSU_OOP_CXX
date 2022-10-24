message(STATUS "Creating library of strategy \"tit_for_tat\"")

add_library(tit_for_tat STATIC
        src/tit_for_tat.cpp)
target_include_directories(tit_for_tat PUBLIC
        include/tit_for_tat
        ${CMAKE_SOURCE_DIR}/libs/strategies/strategy_interface/include/strategy_interface)
target_link_directories(tit_for_tat PUBLIC
        ${CMAKE_BINARY_DIR}/libs/strategies/strategy_interface)
target_link_libraries(tit_for_tat INTERFACE
        strategy_interface)

message(STATUS "Creating tests for library of strategy \"tit_for_tat\"")

enable_testing()
find_package(GTest REQUIRED)
add_executable(tests_tit_for_tat
        test/tests_tit_for_tat.cpp)
target_link_libraries(tests_tit_for_tat PUBLIC
        tit_for_tat
        gtest
        gtest_main)