message(STATUS "Creating dynamic library of strategy \"grim trigger\"")

add_library(grim_trigger SHARED
        src/grim_trigger.cpp)
set_target_properties(grim_trigger PROPERTIES PREFIX "")
target_include_directories(grim_trigger PUBLIC
        include/grim_trigger
        ${CMAKE_SOURCE_DIR}/libs/matrix/include/matrix
        ${CMAKE_SOURCE_DIR}/libs/strategy_interface/include/strategy_interface)

link_directories(
        ${CMAKE_BINARY_DIR}/libs/matrix
        ${CMAKE_BINARY_DIR}/libs/strategy_interface)
target_link_libraries(grim_trigger
        PUBLIC matrix
        INTERFACE strategy_interface)


enable_testing()
find_package(GTest REQUIRED)

add_executable(tests_grim_trigger
        test/tests_grim_trigger.cpp)
target_link_libraries(tests_grim_trigger PUBLIC
        grim_trigger
        gtest
        gtest_main)