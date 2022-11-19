cmake_minimum_required(VERSION 3.23)

set(SUBDIR
        lib/cl_parser
        lib/config_parser
        lib/WAV
        lib/converters
        lib/sound_processor)
set(LIBRARY
        cl_parser
        sound_processor)

project(Task3 CXX)

add_executable(Task3
        src/main.cpp)

foreach(SUBDIR ${SUBDIR})
    add_subdirectory(${SUBDIR})
endforeach(SUBDIR)

target_link_libraries(Task3 PUBLIC ${LIBRARY})