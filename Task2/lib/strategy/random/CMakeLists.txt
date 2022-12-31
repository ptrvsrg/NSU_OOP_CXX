message(STATUS "Creating library of strategy \"random\" ")
add_library(random STATIC
        src/random.cpp)
target_include_directories(random PUBLIC
        include
        ../strategy_interface/include)
target_link_directories(random
        PUBLIC ${CMAKE_BINARY_DIR}lib/strategy/strategy_interface)
target_link_libraries(random
        PUBLIC strategy_interface)