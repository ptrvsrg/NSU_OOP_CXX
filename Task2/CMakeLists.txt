cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(SUBDIR
        libs/cl_parser
        libs/game
        libs/strategies
        libs/abstract_mode
        libs/modes
        libs/strategy_interface
        libs/matrix)
set(LIBRARY
        cl_parser
        game)

project(Task2 CXX)

add_executable(Task2
        src/main.cpp)

foreach(SUBDIR ${SUBDIR})
    add_subdirectory(${SUBDIR})
endforeach(SUBDIR)

target_link_libraries(Task2 ${LIBRARY})