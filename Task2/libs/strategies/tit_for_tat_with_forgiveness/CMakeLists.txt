message(STATUS "Creating library of strategy \"tit_for_tat_with_forgiveness\"")

find_package(Boost COMPONENTS container REQUIRED)
add_library(tit_for_tat_with_forgiveness STATIC
        src/tit_for_tat_with_forgiveness.cpp)
target_include_directories(tit_for_tat_with_forgiveness PUBLIC
        include/tit_for_tat_with_forgiveness
        ${CMAKE_SOURCE_DIR}/libs/strategies/strategy_interface/include/strategy_interface)
target_link_directories(tit_for_tat_with_forgiveness PUBLIC
        ${CMAKE_BINARY_DIR}/libs/strategies/strategy_interface)
target_link_libraries(tit_for_tat_with_forgiveness
        PUBLIC ${Boost_LIBRARIES}
        INTERFACE strategy_interface)
target_compile_definitions(tit_for_tat_with_forgiveness PUBLIC
        -DBOOST_BIND_GLOBAL_PLACEHOLDERS)

message(STATUS "Creating tests for library of strategy \"tit_for_tat_with_forgiveness\"")

enable_testing()
find_package(GTest REQUIRED)
add_executable(tests_tit_for_tat_with_forgiveness
        test/tests_tit_for_tat_with_forgiveness.cpp)
target_link_libraries(tests_tit_for_tat_with_forgiveness PUBLIC
        tit_for_tat_with_forgiveness
        gtest
        gtest_main)