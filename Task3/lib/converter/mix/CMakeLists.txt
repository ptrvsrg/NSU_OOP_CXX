message(STATUS "Creating converter library \"mix\"")

add_library(mix STATIC
        src/mix.cpp)
target_include_directories(mix PUBLIC
        include/mix)

message(STATUS "Creating tests for converter library \"mix\"")

enable_testing()
find_package(GTest REQUIRED)
add_executable(tests_mix
        test/tests_mix.cpp)
target_include_directories(tests_mix PUBLIC
        include/mix)
target_link_libraries(tests_mix PUBLIC
        mix
        gtest
        gtest_main)