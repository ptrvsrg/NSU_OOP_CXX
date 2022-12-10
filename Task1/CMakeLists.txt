cmake_minimum_required(VERSION 3.22.1)

set(LIBRARY_DIR lib)
set(LIBRARY
        big_int
        string_arithmetic)

project(Task1} CXX)

add_executable(Task1
        src/main.cpp)

enable_testing()
foreach(LIBRARY ${LIBRARY})
    add_subdirectory("${LIBRARY_DIR}/${LIBRARY}")
    message(STATUS "Add subdirectory ${LIBRARY_DIR}/${LIBRARY}")
endforeach(LIBRARY)

target_link_libraries(Task1
        ${LIBRARY})