cmake_minimum_required(VERSION 3.23)

project(Task4 CXX)

set(CMAKE_CXX_STANDARD 14)

set(SUBDIRS
        lib/tuple_utility)

enable_testing()
foreach(SUBDIR ${SUBDIRS})
    add_subdirectory(${SUBDIR})
endforeach(SUBDIR)

add_executable(example
        example/main.cpp)
