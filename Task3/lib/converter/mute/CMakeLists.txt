message(STATUS "Creating converter library \"mute\"")

add_library(mute STATIC
        src/mute.cpp)
target_include_directories(mute
        PUBLIC include
        PUBLIC ../converter_interface/include
        PUBLIC ../converter_errors/include)
target_link_directories(mute
        PUBLIC ${CMAKE_BINARY_DIR}/lib/converter/converter_interface)
target_link_libraries(mute
        PUBLIC converter_interface
        PUBLIC converter_errors)

message(STATUS "Creating tests for converter library \"mute\"")

find_package(GTest REQUIRED)
add_executable(tests_mute
        test/tests_mute.cpp)
target_link_libraries(tests_mute
        PUBLIC mute
        PUBLIC gtest
        PUBLIC gtest_main)
add_test(NAME tests_mute
        COMMAND tests_mute
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)