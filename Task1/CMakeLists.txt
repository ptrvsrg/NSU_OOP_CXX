cmake_minimum_required(VERSION 3.22.1)

set(LIBRARY_DIR lib)
set(LIBRARY
        big_int
        string_arithmetic)

project(Task1} CXX)

enable_testing()
foreach(LIBRARY ${LIBRARY})
    add_subdirectory("${LIBRARY_DIR}/${LIBRARY}")
    message(STATUS "Add subdirectory ${LIBRARY_DIR}/${LIBRARY}")
endforeach(LIBRARY)

# Example

add_executable(Task1
        example/main.cpp)
target_link_libraries(Task1
        ${LIBRARY})
add_test(NAME launch_example
        COMMAND Task1 11111111111 10000000000
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/example)