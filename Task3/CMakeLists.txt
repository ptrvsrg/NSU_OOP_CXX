cmake_minimum_required(VERSION 3.23)

set(SUBDIR
        lib/cl_parser
        lib/config_parser
        lib/WAV
        lib/converter
        lib/sound_processor)
set(LIBRARY
        cl_parser
        sound_processor)

project(Task3 CXX)

add_executable(Task3
        example/main.cpp)

enable_testing()
foreach(SUBDIR ${SUBDIR})
    add_subdirectory(${SUBDIR})
endforeach(SUBDIR)

target_link_libraries(Task3 PUBLIC ${LIBRARY})