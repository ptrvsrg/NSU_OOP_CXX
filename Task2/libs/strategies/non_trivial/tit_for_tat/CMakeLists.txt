message(STATUS "Creating dynamic library of strategy \"tit_for_tat\"")

add_library(tit_for_tat SHARED
        src/tit_for_tat.cpp)
set_target_properties(tit_for_tat PROPERTIES PREFIX "")
target_include_directories(tit_for_tat PUBLIC
        include/tit_for_tat
        ${CMAKE_SOURCE_DIR}/libs/matrix/include/matrix
        ${CMAKE_SOURCE_DIR}/libs/strategy_interface/include/strategy_interface)

link_directories(
        ${CMAKE_BINARY_DIR}/libs/matrix
        ${CMAKE_BINARY_DIR}/libs/strategy_interface)
target_link_libraries(tit_for_tat INTERFACE
        matrix
        strategy_interface)


enable_testing()
find_package(GTest REQUIRED)

add_executable(tests_tit_for_tat
        test/tests_tit_for_tat.cpp)
target_link_libraries(tests_tit_for_tat PUBLIC
        tit_for_tat
        gtest
        gtest_main)