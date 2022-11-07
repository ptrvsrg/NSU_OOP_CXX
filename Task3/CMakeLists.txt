cmake_minimum_required(VERSION 3.23)

set(SUBDIR
        lib/cl_parser
        lib/config_parser)
set(LIBRARY
        cl_parser)

project(Task3 CXX)

add_executable(Task3
        src/main.cpp)

foreach(SUBDIR ${SUBDIR})
    add_subdirectory(${SUBDIR})
endforeach(SUBDIR)

target_link_libraries(Task3 ${LIBRARY})