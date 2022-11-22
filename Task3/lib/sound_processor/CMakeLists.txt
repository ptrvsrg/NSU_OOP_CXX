message(STATUS "Creating library \"sound_processor\"")

add_library(sound_processor STATIC
        src/sound_processor.cpp
        src/sound_processor_errors.cpp)
target_include_directories(sound_processor
        PUBLIC include)
target_link_directories(sound_processor
        PUBLIC ${CMAKE_BINARY_DIR}/lib/config_parser
        PUBLIC ${CMAKE_BINARY_DIR}/lib/converters
        PUBLIC ${CMAKE_BINARY_DIR}/lib/WAV)
target_link_libraries(sound_processor
        PUBLIC config_parser
        PUBLIC converter_creator
        PUBLIC WAV)

message(STATUS "Creating tests for library \"sound_processor\"")

find_package(GTest REQUIRED)
add_executable(tests_sound_processor
        test/tests_sound_processor.cpp)
target_link_libraries(tests_sound_processor
        PUBLIC sound_processor
        PUBLIC gtest
        PUBLIC gtest_main)
add_test(NAME tests_sound_processor
        COMMAND tests_sound_processor
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test)