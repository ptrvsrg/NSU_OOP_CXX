message(STATUS "Creating converter library \"mute\"")

add_library(mute STATIC
        src/mute.cpp
        src/mute_errors.cpp)
target_include_directories(mute PUBLIC
        include/mute
        ${CMAKE_SOURCE_DIR}/lib/WAV/include)
target_link_directories(mute PUBLIC
        ${CMAKE_BINARY_DIR}/lib/WAV)
target_link_libraries(mute PUBLIC
        WAV)

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