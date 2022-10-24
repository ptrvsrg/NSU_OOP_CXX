message(STATUS "Creating library of strategy \"pavlov\"")

find_package(Boost COMPONENTS container REQUIRED)
add_library(pavlov STATIC
        src/pavlov.cpp)
target_include_directories(pavlov PUBLIC
        include/pavlov
        ${CMAKE_SOURCE_DIR}/libs/strategies/strategy_creator/include/strategy_creator
        ${CMAKE_SOURCE_DIR}/libs/strategies/strategy_interface/include/strategy_interface)
target_link_directories(pavlov PUBLIC
        ${CMAKE_BINARY_DIR}/libs/strategies/strategy_creator
        ${CMAKE_BINARY_DIR}/libs/strategies/strategy_interface)
target_link_libraries(pavlov
        PUBLIC strategy_creator
        PUBLIC ${Boost_LIBRARIES}
        INTERFACE strategy_interface)
target_compile_definitions(pavlov PUBLIC -DBOOST_BIND_GLOBAL_PLACEHOLDERS)

message(STATUS "Creating tests for library of strategy \"pavlov\"")

enable_testing()
find_package(GTest REQUIRED)
add_executable(tests_pavlov
        test/tests_pavlov.cpp)
target_link_libraries(tests_pavlov PUBLIC
        pavlov
        gtest
        gtest_main)