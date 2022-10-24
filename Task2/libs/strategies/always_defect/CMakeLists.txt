message(STATUS "Creating library of strategy \"always_defect\"")

add_library(always_defect STATIC
        src/always_defect.cpp)
target_include_directories(always_defect PUBLIC
        include/always_defect
        ${CMAKE_SOURCE_DIR}/libs/strategies/strategy_interface/include/strategy_interface)
target_link_directories(always_defect PUBLIC
        ${CMAKE_BINARY_DIR}/libs/strategies/strategy_interface)
target_link_libraries(always_defect INTERFACE
        strategy_interface)