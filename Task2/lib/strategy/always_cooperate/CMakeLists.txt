message(STATUS "Creating library of strategy \"always_cooperate\" ")
add_library(always_cooperate STATIC
        src/always_cooperate.cpp)
target_include_directories(always_cooperate PUBLIC
        include
        ../strategy_interface/include)
target_link_directories(always_cooperate
        PUBLIC ${CMAKE_BINARY_DIR}lib/strategy/strategy_interface)
target_link_libraries(always_cooperate
        PUBLIC strategy_interface)