message(STATUS "Creating library of strategy \"always_defect\" ")
add_library(always_defect STATIC
        src/always_defect.cpp)
target_include_directories(always_defect PUBLIC
        include
        ../strategy_interface/include)
target_link_directories(always_defect
        PUBLIC ${CMAKE_BINARY_DIR}lib/strategy/strategy_interface)
target_link_libraries(always_defect
        PUBLIC strategy_interface)