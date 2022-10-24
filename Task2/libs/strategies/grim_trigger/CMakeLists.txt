message(STATUS "Creating library of strategy \"grim trigger\"")

add_library(grim_trigger STATIC
        src/grim_trigger.cpp)
target_include_directories(grim_trigger PUBLIC
        include/grim_trigger
        ${CMAKE_SOURCE_DIR}/libs/strategies/strategy_interface/include/strategy_interface)
target_link_directories(grim_trigger PUBLIC
        ${CMAKE_BINARY_DIR}/libs/strategies/strategy_interface)
target_link_libraries(grim_trigger INTERFACE
        strategy_interface)

message(STATUS "Creating tests for library of strategy \"grim trigger\"")

enable_testing()
find_package(GTest REQUIRED)
add_executable(tests_grim_trigger
        test/tests_grim_trigger.cpp)
target_link_libraries(tests_grim_trigger PUBLIC
        grim_trigger
        gtest
        gtest_main)