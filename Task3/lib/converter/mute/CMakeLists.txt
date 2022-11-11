message(STATUS "Creating converter library \"mute\"")

add_library(mute STATIC
        src/mute.cpp
        src/mute_errors.cpp)
target_include_directories(mute PUBLIC
        include/mute)

message(STATUS "Creating tests for converter library \"mute\"")

enable_testing()
find_package(GTest REQUIRED)
add_executable(tests_mute
        test/tests_mute.cpp)
target_include_directories(tests_mute PUBLIC
        include/mute)
target_link_libraries(tests_mute PUBLIC
        mute
        gtest
        gtest_main)