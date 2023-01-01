cmake_minimum_required(VERSION 3.23)

project(Task4 CXX)

set(SUBDIRS
        lib/CSV_parser
        lib/tuple_utility)

enable_testing()
foreach(SUBDIR ${SUBDIRS})
    add_subdirectory(${SUBDIR})
endforeach(SUBDIR)

# Example

add_executable(Task4
        example/main.cpp)
target_link_libraries(Task4
        PUBLIC CSV_parser)

add_test(NAME launch_example
        COMMAND Task4
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/example)
