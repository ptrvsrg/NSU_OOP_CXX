message(STATUS "Creating library \"converter_creator\"")

add_library(converter_creator STATIC
        src/converter_creator.cpp
        src/converter_creator_errors.cpp)
target_include_directories(converter_creator
        PUBLIC include
        PUBLIC ../converter_interface/include
        PUBLIC ../mute/include
        PUBLIC ../mix/include)
target_link_directories(converter_creator
        PUBLIC ${CMAKE_BINARY_DIR}/lib/converter/converter_interface
        PUBLIC ${CMAKE_BINARY_DIR}/lib/converter/mute
        PUBLIC ${CMAKE_BINARY_DIR}/lib/converter/mix)
target_link_libraries(converter_creator
        PUBLIC converter_interface
        PUBLIC mute
        PUBLIC mix)

message(STATUS "Creating tests for converter library \"converter_creator\"")

find_package(GTest REQUIRED)
add_executable(tests_converter_creator
        test/tests_converter_creator.cpp)
target_link_libraries(tests_converter_creator
        PUBLIC converter_creator
        PUBLIC gtest
        PUBLIC gtest_main)
add_test(NAME tests_converter_creator
        COMMAND tests_converter_creator
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)