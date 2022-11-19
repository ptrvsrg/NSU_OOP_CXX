# MUTE converters
message(STATUS "Creating converter library \"mute\"")

add_library(mute STATIC
        src/mute.cpp
        src/converter_errors.cpp)
target_include_directories(mute
        PUBLIC include/converter_interface
        PUBLIC include/mute)

message(STATUS "Creating tests for converter library \"mute\"")

enable_testing()
find_package(GTest REQUIRED)
add_executable(tests_mute
        test/tests_mute.cpp)
target_include_directories(tests_mute
        PUBLIC include/mute)
target_link_libraries(tests_mute
        PUBLIC mute
        PUBLIC gtest
        PUBLIC gtest_main)

# MIX converters
message(STATUS "Creating converter library \"mix\"")

add_library(mix STATIC
        src/mix.cpp
        src/converter_errors.cpp)
target_include_directories(mix
        PUBLIC include/converter_interface
        PUBLIC include/mix)

message(STATUS "Creating tests for converter library \"mix\"")

enable_testing()
find_package(GTest REQUIRED)
add_executable(tests_mix
        test/tests_mix.cpp)
target_include_directories(tests_mix
        PUBLIC include/mix)
target_link_libraries(tests_mix
        PUBLIC mix
        PUBLIC gtest
        PUBLIC gtest_main)

# Converter creator
message(STATUS "Creating converter library \"converter_creator\"")

add_library(converter_creator STATIC
        src/converter_creator.cpp
        src/converter_creator_errors.cpp)
target_include_directories(converter_creator
        PUBLIC include/converter_interface
        PUBLIC include/converter_creator
        PUBLIC include/mute
        PUBLIC include/mix)
target_link_libraries(converter_creator
        PUBLIC mute
        PUBLIC mix)
