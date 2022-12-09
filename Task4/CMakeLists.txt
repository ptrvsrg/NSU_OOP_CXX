cmake_minimum_required(VERSION 3.23)

project(Task4 CXX)

set(SUBDIRS
        lib/CSV_parser
        lib/tuple_utility)

enable_testing()
foreach(SUBDIR ${SUBDIRS})
    add_subdirectory(${SUBDIR})
endforeach(SUBDIR)

add_executable(example
        example/main.cpp)
target_link_libraries(example
        PUBLIC CSV_parser)
