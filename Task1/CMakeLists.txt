cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(PROJECT_NAME Task1)
set(SOURCE_DIR src)
set(SOURCE ${SOURCE_DIR}/main.cpp)
set(LIBRARY_DIR lib)
set(LIBRARY google_tests big_int string_arithmetic)

project(${PROJECT_NAME} CXX)

add_executable(${PROJECT_NAME} ${SOURCE})

foreach(LIBRARY ${LIBRARY})
    add_subdirectory("${LIBRARY_DIR}/${LIBRARY}")
    message(STATUS "Add subdirectory ${LIBRARY_DIR}/${LIBRARY}")
endforeach(LIBRARY)

target_link_libraries(${PROJECT_NAME} ${LIBRARY})