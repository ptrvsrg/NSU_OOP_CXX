message(STATUS "Creating library \"abstract_mode\"")


add_library(abstract_mode STATIC
        src/abstract_mode.cpp
        src/loaded_strategy.cpp)
set_target_properties(abstract_mode PROPERTIES PREFIX "")
target_include_directories(abstract_mode PUBLIC
        include/abstract_mode
        include/loaded_strategy
        ${CMAKE_SOURCE_DIR}/libs/matrix/include/matrix
        ${CMAKE_SOURCE_DIR}/libs/strategy_interface/include/strategy_interface)

link_directories(
        ${CMAKE_BINARY_DIR}/libs/matrix
        ${CMAKE_BINARY_DIR}/libs/strategy_interface)
target_link_libraries(abstract_mode
        PUBLIC matrix
        INTERFACE strategy_interface)

enable_testing()
find_package(GTest REQUIRED)

add_executable(tests_loaded_strategy
        test/tests_loaded_strategy.cpp
        src/loaded_strategy.cpp)
target_include_directories(tests_loaded_strategy PUBLIC
        include/loaded_strategy
        ${CMAKE_SOURCE_DIR}/libs/matrix/include/matrix
        ${CMAKE_SOURCE_DIR}/libs/strategy_interface/include/strategy_interface)
target_link_libraries(tests_loaded_strategy PUBLIC
        gtest
        gtest_main)