cmake_minimum_required(VERSION 3.23)

set(SUBDIR
        lib/cl_parser
        lib/iostream_errors
        lib/config_parser
        lib/WAV
        lib/converter
        lib/sound_processor)
set(LIBRARY
        cl_parser
        sound_processor)
file(GLOB
        CONVERTER_SOURCE_DIRS
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/converter/*")
list(REMOVE_ITEM
        CONVERTER_SOURCE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/converter/converter_creator
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/converter/converter_errors
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/converter/converter_interface
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/converter/CMakeLists.txt)
string(REPLACE
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/converter/"
        ";${CMAKE_CURRENT_BINARY_DIR}/lib/converter/"
        CONVERTER_BINARY_DIRS
        ${CONVERTER_SOURCE_DIRS})
string(REPLACE
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/converter/"
        ";"
        CONVERTERS
        ${CONVERTER_SOURCE_DIRS})

project(Task3)

enable_testing()
foreach(SUBDIR ${SUBDIR})
    add_subdirectory(${SUBDIR})
endforeach(SUBDIR)

# Example

add_executable(Task3
        example/main.cpp)
target_link_libraries(Task3 PUBLIC ${LIBRARY})

add_test(NAME launch_example
        COMMAND Task3   --config
                            config.txt
                        --output
                            output.wav
                        --input
                            input0.wav
                            input1.wav
                            input2.wav
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/example)